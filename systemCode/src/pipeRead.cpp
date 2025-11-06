#include "func.h"

void test1( int argc , char * argv[]){  // 读pipe
    ARGS_CHECK(argc , 2);
    int fdr = open(argv[1] , O_RDONLY);
    ERROR_CHECK(fdr ,-1 , "open");

    printf("read side is opened \n");
    
    close(fdr);
}


void test2( int argc , char * argv[]){  // 全双工
    ARGS_CHECK(argc , 3);
    int fdr1 = open(argv[1] , O_RDONLY);
    int fdw2 = open(argv[2] , O_WRONLY);
    ERROR_CHECK(fdr1 ,-1 , "open");
    ERROR_CHECK(fdw2 ,-1 , "open");
    printf("read side is opened \n");
    
    close(fdr1);
    close(fdw2);
}

void test3(int argc , char * argv[]){   //重定向 + 管道
    ARGS_CHECK(argc , 2);
    int fd = open(argv[1] , O_RDONLY);
    ERROR_CHECK(fd , -1, " open");

    char buf[1024] = {0};
    ssize_t ret =  read(fd , buf , sizeof(buf));
    ERROR_CHECK(ret , -1 , "read");
    printf("%d  %s", ret , buf);

    close(fd);
} 


void test4(int argc , char * argv[]){   //全双工
    ARGS_CHECK(argc , 3);

    int fdr = open(argv[1] , O_RDONLY);      
    ERROR_CHECK(fdr , -1, " open");

    int fdw = open(argv[2] , O_WRONLY);
    ERROR_CHECK(fdw , -1, " open");

    // char buf[1024] = {0};
    // ssize_t ret =  read(fdr , buf , sizeof(buf));
    // ERROR_CHECK(ret , -1 , "read");
    // printf("%d  %s", ret , buf);

    printf("azhen is connected \n");

    close(fdr);
     close(fdw);
} 

void test5(int argc , char * argv[]){   ////持续写 ， 测试写阻塞
    ARGS_CHECK(argc , 2);

    int fd = open(argv[1] , O_RDONLY);      
    ERROR_CHECK(fd , -1, " open");

    
    char buf[4096];
    sleep(5);

    while(1){
        read(fd , buf , 4096);
        printf("read one\n")  ;
        sleep(5);
    }


    close(fd);
    
} 


void test6(int argc , char * argv[]){   //O_RDWR  非阻塞打开一端  ：  可以打开两次  // 半双工
    ARGS_CHECK(argc , 2);
    int fd1 = open(argv[1], O_RDWR) ;   ERROR_CHECK(fd1 , -1 ,"open");  // 写
    int fd2 = open(argv[1], O_RDWR );   ERROR_CHECK(fd2 , -1 ,"open");  // 读

    printf("pipe is open \n");   // 不会阻塞  ， 半双工


    fd_set rdset ;
    fd_set wrset;

    int cnt2 = 0;int cnt1 = 0;
    char buf[4096] = {0};
    while(1){
        FD_ZERO(&rdset);
        FD_ZERO(&wrset);
        FD_SET(fd1, &wrset);
        FD_SET(fd2, &rdset);

        sleep(1);

        int ret = select(fd2+1 , &rdset , &wrset , NULL, NULL );

        if(FD_ISSET(fd2, &rdset )){      // 可以读
            printf("read ready cnt1 = %d  \n" ,cnt1 ++);

            ret = read(fd2, buf, 2048);

            if(ret == 0){ 
                 break;
            }
            
        }
        if(FD_ISSET(fd1, &wrset )){    // 可以写
            printf("write  ready cnt2 = %d  \n" ,cnt2 ++);

            ret = write(fd1, buf, 4096);

        }
    }

}

typedef struct 
{
    unsigned int len = 0;
    char buf[4092] = {0}; 
}Data;

void test7(int argc , char * argv[]){  // 传文件  
    ARGS_CHECK(argc , 2);

    int fdr = open(argv[1] , O_RDONLY);
    ERROR_CHECK(fdr , -1 , "open");

    
    sleep(1);

    Data data;
    // 读文件名
    int ret = read(fdr ,&data.len , sizeof(data.len)); ERROR_CHECK(ret , -1 , "read");
    ret = read(fdr ,data.buf , data.len);      ERROR_CHECK(ret , -1 , "read");

    char path[4096] = {0};
    char dir[] = "dir1";
    mkdir(dir , 0777);
   
    sprintf(path , "%s%s%s", dir ,"/", data.buf);
    int fdFile = open(path , O_RDWR|O_CREAT|O_TRUNC , 0666);
    ERROR_CHECK(fdFile , -1 ,"open");

   
    while( (ret = read( fdr , &data.len, sizeof(data.len))) != 0  ){
        ERROR_CHECK(ret , -1 , "read");
        ret = read( fdr , data.buf, data.len); ERROR_CHECK(ret , -1 , "read");
        write(fdFile, data.buf , ret);
    }

    close(fdr);
}

int main(int argc , char * argv[]){
    test7(argc , argv);
}