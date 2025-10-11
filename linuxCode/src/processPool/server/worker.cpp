
#include "processPool.h"

int makeWorker(int workerNum , workerdata_t * workArr){

    for(int i =0;i< workerNum ; ++i){
        int pipefd[2];

        socketpair(AF_LOCAL , SOCK_STREAM , 0 , pipefd); // 父子共用

        pid_t pid = fork();

        if(pid == 0){    //子进程   // 防止一生二， 二生四
            close(pipefd[1]);
            workLoop(pipefd[0]);
        }

        close(pipefd[0]);
        workArr[i].status = FREE;  //父进程
        workArr[i].pid = pid;   
        workArr[i].pipesocketfd = pipefd[1];  //父进程进程修改 ， 保存的是父进程的 pipefd
        printf("i = %d , pid = %d \n" , i , pid );
    }
 
    return 0;
}

typedef struct{
    int length;
    char data[1000]; //可以保存任何数据 //1024 数据上限
}train_t;
//传统的建立用户态buf
int transFile1(int netfd ){
    train_t train;
    bzero(&train,sizeof(train));
    char filename[] = "copy.pdf";
    train.length = strlen(filename);
    memcpy(train.data , filename, strlen(filename));
    send(netfd , &train,  sizeof(train.length) +train.length,MSG_NOSIGNAL);
    int fd = open(filename , O_RDWR);

    struct stat statbuf ;
    fstat(fd , &statbuf);
    train.length = sizeof(off_t);
    printf("filesize =  %ld\n",statbuf.st_size );
    memcpy(train.data , &statbuf.st_size ,train.length);
    send(netfd , &train,  sizeof(train.length) + train.length,MSG_NOSIGNAL);
 
    char buf[1000] = {0};
    while(1){ //读大文件
        
        ssize_t sret = read(fd , buf , sizeof(train.data));
        errorEqualCheck(sret ,-1, "read");
        train.length = sret;
        memcpy(train.data , buf, sret);
       
        sret = send(netfd , &train,  sizeof(train.length) +train.length,MSG_NOSIGNAL);
        if(sret == 0 || sret == -1){
             break;  // 最后一次 可以发一个空的火车
        }
    }

    return 0;

 }
 //mmap 建立内存缓冲区
int transFile2(int netfd ){
    train_t train;
    bzero(&train,sizeof(train));
    char filename[] = "copy.pdf";
    train.length = strlen(filename);
    memcpy(train.data , filename, strlen(filename));
    send(netfd , &train,  sizeof(train.length) +train.length,MSG_NOSIGNAL);
    int fd = open(filename , O_RDWR);

    struct stat statbuf ;
    fstat(fd , &statbuf);
    train.length = sizeof(off_t);
    printf("filesize =  %ld\n",statbuf.st_size );
    memcpy(train.data , &statbuf.st_size ,train.length);
    send(netfd , &train,  sizeof(train.length) + train.length,MSG_NOSIGNAL);
    
    //statbuf.st_size 映射区大小 = 文件大小
    char *p = (char *)mmap(NULL ,statbuf.st_size,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0 );
    errorEqualCheck(p,MAP_FAILED,"mmap");

    off_t cursize = 0;
    while(1){
        if(cursize >= statbuf.st_size){
            break;
        }
        if(statbuf.st_size - cursize >= 1000){
            train.length = 1000;
        }else{
            train.length = statbuf.st_size - cursize;
        }
        send(netfd , &train.length,  sizeof(train.length) ,MSG_NOSIGNAL);
        send(netfd , p+cursize, train.length ,MSG_NOSIGNAL);
        cursize += train.length;
    }
    train.length = 0;
    send(netfd , &train.length,  sizeof(train.length) ,MSG_NOSIGNAL);
    munmap(p,statbuf.st_size);
    return 0;
 }

//发送大火车箱
int transFile3(int netfd ){
    train_t train;
    bzero(&train,sizeof(train));
    char filename[] = "copy.pdf";
    train.length = strlen(filename);
    memcpy(train.data , filename, strlen(filename));
    send(netfd , &train,  sizeof(train.length) +train.length,MSG_NOSIGNAL);

    int fd = open(filename , O_RDWR);
    struct stat statbuf ;
    fstat(fd , &statbuf);
    train.length = statbuf.st_size;
    printf("filesize =  %ld\n",statbuf.st_size );
    // memcpy(train.data , &statbuf.st_size ,train.length);
    // send(netfd , &train,  sizeof(train.length) + train.length,MSG_NOSIGNAL);
    
    //statbuf.st_size 映射区大小 = 文件大小
    char *p = (char *)mmap(NULL ,statbuf.st_size,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0 );
    errorEqualCheck(p,MAP_FAILED,"mmap");

    //off_t cursize = 0;
    // while(1){
    //     if(cursize >= statbuf.st_size){
    //         break;
    //     }
    //     if(statbuf.st_size - cursize >= 1000){
    //         train.length = 1000;
    //     }else{
    //         train.length = statbuf.st_size - cursize;
    //     }
    //     send(netfd , &train.length,  sizeof(train.length) ,MSG_NOSIGNAL);
    //     send(netfd , p+cursize, train.length ,MSG_NOSIGNAL);
    //     cursize += train.length;
    // }
    
    send(netfd , &train.length,  sizeof(train.length) ,MSG_NOSIGNAL);
    send(netfd , p, train.length ,MSG_NOSIGNAL);

    train.length = 0;
    send(netfd , &train.length,  sizeof(train.length) ,MSG_NOSIGNAL);
    munmap(p,statbuf.st_size);
    return 0;
 }
 
//发送大火车箱 snedfile
int transFile4(int netfd ){
    train_t train;
    bzero(&train,sizeof(train));
    char filename[] = "copy.pdf";
    train.length = strlen(filename);
    memcpy(train.data , filename, strlen(filename));
    send(netfd , &train,  sizeof(train.length) +train.length,MSG_NOSIGNAL);

    int fd = open(filename , O_RDWR);
    struct stat statbuf ;
    fstat(fd , &statbuf);
    train.length = statbuf.st_size;
    printf("filesize =  %ld\n",statbuf.st_size );
   
    sendfile(netfd , fd, NULL, statbuf.st_size);
    

    train.length = 0;
    send(netfd , &train.length,  sizeof(train.length) ,MSG_NOSIGNAL);
    
    return 0;
 }
int workLoop(int sockfd){
    while(1){
        int netfd;
        int exitflag;
        recvFd(sockfd , &netfd , &exitflag); //接收任务
        if(exitflag ==1){
            printf("I am going to exiting \n");
            exit(0);
        }
        printf("begin work \n");//执行任务

        transFile3(netfd);

        printf("end work \n");
        //任务完成之后 ，向主人进程发送自己的PID 
        //sleep(10);
        pid_t pid = getpid();
        if(pid == 0){
            printf("----------------------70707707070\n");
        }
        send( sockfd , &pid ,sizeof(pid),0  ); //sockfd socketpair的

        close(netfd);   
        printf("----------------------333333\n");
        //sendFd 中的sendmsg 是传内核数据结构的
        //父子之间的不同通信 ， 发个数据之类的之间从socketpair 的send 就是
    }
}
