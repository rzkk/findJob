#include "threadPool.h"


// int clientTest(int argc ,char * argv[]){
//     argsCheck(argc , 3);

//     int sockfd = socket(AF_INET , SOCK_STREAM , 0 );

//     struct sockaddr_in serverAddr;   // 地址结构
//     serverAddr.sin_family = AF_INET;
//     serverAddr.sin_port = htons(atoi(argv[2]));
//     serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

//     int ret = connect(sockfd , (struct sockaddr *)&serverAddr, sizeof(serverAddr) );
//     errorEqualCheck(ret, -1 , "bind");

//     return 0;
   
// }
typedef struct{
    int length;
    char data[1000]; //可以保存任何数据 //1024 数据上限
}train_t;

int recvn(int sockfd , void * buf , long total){
    char *p = (char *)buf;
    long cursize = 0;
    while(cursize < total){
        ssize_t ret = recv(sockfd , p+ cursize , total - cursize , 0);
        if(ret == 0) return 1;
        cursize += ret;
    }
    return 0;
}
int recvfile3(int sockfd){ // 一次收全部
    train_t train;
    bzero(&train,sizeof(train));
    

    char filename[128] = {0};
    ssize_t sret = recvn(sockfd , &train.length, sizeof(train.length));
    //if(sret ==0 ) return 0;
    sret = recvn(sockfd , filename, train.length);
    //if(sret ==0 ) return 0;

    cout<<filename<< " filename  " <<endl;
    int fd = open(filename , O_CREAT|O_RDWR|O_TRUNC , 0666);

    off_t filesize;
    sret = recvn(sockfd , &train.length, sizeof(train.length));
    filesize = train.length;
    cout<<filesize<<endl;  

    ftruncate(fd, filesize);   //文件扩张
    char * p = (char*)mmap(NULL ,filesize,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0 );

    sret = recvn(sockfd , p, filesize); 
    
    munmap(p,filesize);
    return sret;
}
int recvfile2(int sockfd){  //recvn

    train_t train;
    bzero(&train,sizeof(train));
    

    char filename[128] = {0};
    ssize_t sret = recvn(sockfd , &train.length, sizeof(train.length));
   // if(sret ==0 ) return 0;
    sret = recvn(sockfd , filename, train.length);
    //if(sret ==0 ) return 0;

    cout<<filename<< " filename  " <<endl;
    int fd = open(filename , O_CREAT|O_RDWR|O_TRUNC , 0666);
    char buf[4096] = {0};


    
    off_t filesize;
    sret = recvn(sockfd , &train.length, sizeof(train.length));
    sret = recvn(sockfd , &filesize, train.length);

    //printf("filesieze %d \n", filesize);
    off_t cursize = 0;
    off_t lastsize = 0; //上次的文件大小
    off_t slice = filesize /10000; // 打印进度条的最小分片
     while(1){
        sret = recvn(sockfd , &train.length, sizeof(train.length)); 
        if(sret ==0 ) return 0;
        //errorEqualCheck(sret,-1 , "recv1");
        
        sret = recvn(sockfd , buf, train.length);
        errorEqualCheck(sret,-1 , "recv2");
        if(train.length != 1000)
            cout<<train.length<<endl;
        if(sret ==0 ) return 0;

        cursize += sret ;
        if(cursize - lastsize > slice){
            printf("%5.2lf%%\r", cursize*(100.0) / filesize);
            fflush(stdout); //刷新缓冲区
            lastsize = cursize;
        }
       
        sret =  write(fd, buf , sret );
        //errorEqualCheck(sret,-1 , "write");
    }
    printf("100%\n");
    return sret;
}
int recvfile1(int sockfd){

    train_t train;
    bzero(&train,sizeof(train));
    

    char filename[128] = {0};
    ssize_t sret = recv(sockfd , &train.length, sizeof(train.length),MSG_WAITALL);
    //if(sret ==0 ) return 0;
    sret = recv(sockfd , filename, train.length,MSG_WAITALL);
    //if(sret ==0 ) return 0;

    cout<<filename<< " filename  " <<endl;
    int fd = open(filename , O_CREAT|O_RDWR|O_TRUNC , 0666);
    char buf[4096] = {0};


    
    off_t filesize;
    sret = recv(sockfd , &train.length, sizeof(train.length),MSG_WAITALL);
    sret = recv(sockfd , &filesize, train.length,MSG_WAITALL);

    //printf("filesieze %d \n", filesize);
    off_t cursize = 0;
    off_t lastsize = 0; //上次的文件大小
    off_t slice = filesize /10000; // 打印进度条的最小分片
     while(1){
        sret = recv(sockfd , &train.length, sizeof(train.length), MSG_WAITALL); 
        if(sret ==0 ) return 0;
        //errorEqualCheck(sret,-1 , "recv1");
        
        sret = recv(sockfd , buf, train.length,MSG_WAITALL);
        errorEqualCheck(sret,-1 , "recv2");
        if(train.length != 1000)
            cout<<train.length<<endl;
        if(sret ==0 ) return 0;

        cursize += sret ;
        if(cursize - lastsize > slice){
            printf("%5.2lf%%\r", cursize*(100.0) / filesize);
            fflush(stdout); //刷新缓冲区
            lastsize = cursize;
        }
       
        sret =  write(fd, buf , sret );
        //errorEqualCheck(sret,-1 , "write");
    }
    printf("100%\n");
    return sret;
}

void clientTest(int argc ,char * argv[]){   //客户端
    argsCheck(argc , 3); 

    int sockfd = socket(AF_INET , SOCK_STREAM , 0 );

    struct sockaddr_in serverAddr;   // 地址结构
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    int ret = connect(sockfd , (struct sockaddr *)&serverAddr, sizeof(serverAddr) );
    errorEqualCheck(ret, -1 , "connect");

    
    fd_set rdset; // 只监听读事件
    char buf[4096] = {0};
    
    while(1){
        FD_ZERO(&rdset);              //每次监听开始都要重置监听集合
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sockfd, &rdset);       //socket  和stdin 加入监听
        select(sockfd+1 , &rdset , NULL ,NULL ,NULL);
        if(FD_ISSET(sockfd,&rdset)){
            //memset(buf,0,sizeof(buf));
            //int ret = read(sockfd,buf,sizeof(buf));
            if (recvfile3(sockfd) == 0){
                close(sockfd);
                printf(" byebye  lo \n");
                break;
            }
           
            
        }
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            //memset(buf,0,sizeof(buf));
            bzero(buf, sizeof(buf)); // 
            int ret =  read(STDIN_FILENO,buf,sizeof(buf));
            if (ret == 0){
                close(sockfd);
                printf("客户端断开,byebye \n");
                break;
            }
            write(sockfd,buf,ret);
        }
    }
}

int main(int argc ,char * argv[]){
    clientTest(argc, argv);
}


