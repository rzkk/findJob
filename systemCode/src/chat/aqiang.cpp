#include"func.h"

//./qiang 1.pipe 2.pipe
void test1(int argc , char * argv[]){
    ARGS_CHECK(argc ,3);

    int fdw = open(argv[1] , O_WRONLY);
    ERROR_CHECK(fdw , -1 , "open");

    int fdr = open(argv[2] , O_RDONLY);
    ERROR_CHECK(fdr , -1, "open");

    printf("aqinag is connected \n");
    char buf[4096] = {0};
    ssize_t ret = 0;

     while(1){

        memset(buf , 0 , sizeof(buf));
        ret = read(STDIN_FILENO , buf , sizeof(buf));  ERROR_CHECK(ret , -1 , "read");
        ret = write(fdw , buf , ret); ERROR_CHECK(ret , -1 , "write");
       


        memset(buf , 0 , sizeof(buf));
        ret =  read(fdr , buf , sizeof(buf));  ERROR_CHECK(ret , -1 , "read");

        printf("             azhen :  %s    ",  buf);
    }

}

//./qiang 1.pipe 2.pipe  //IO 多路复用
void test2(int argc , char * argv[]){
    ARGS_CHECK(argc ,3);
    int fdw = open(argv[1] , O_WRONLY);
    ERROR_CHECK(fdw , -1 , "open");
    int fdr = open(argv[2] , O_RDONLY);
    ERROR_CHECK(fdr , -1, "open");
    printf("aqinag is connected \n");
    char buf[4096] = {0};
    ssize_t ret = 0;
    fd_set rdset; // fd_set 申请内存
    struct timeval timeout;
    while(1){  // 每次循环开始 重置监听集合  
        FD_ZERO(&rdset); // 清零 ， rdset 最开始是监听集合
        FD_SET(STDIN_FILENO , & rdset);
        FD_SET(fdr , & rdset);
 
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;

        ret = select(fdr+1 , &rdset , NULL , NULL ,NULL);

        ERROR_CHECK(ret , -1 , "select");
        //select 返回说明 ， fdr or stdin 中有一个就绪了， rdset  是就绪集合
        if(ret == 0){
            printf("timeout \n");
            time_t now = time(NULL);
            printf("%s \n" , ctime(&now));
            continue;
        }
        if(FD_ISSET(fdr , &rdset)){  // 是否管道就绪
            memset(buf , 0 , sizeof(buf));
            ret =  read(fdr , buf , sizeof(buf));  ERROR_CHECK(ret , -1 , "read");

            if(ret == 0){
                printf("对方关闭 ,  退出\n");
                break;
            }
            printf("             azhen :  %s",  buf);
        }

        if(FD_ISSET(STDIN_FILENO , &rdset)){
            memset(buf , 0 , sizeof(buf));
            ret = read(STDIN_FILENO , buf , sizeof(buf));  ERROR_CHECK(ret , -1 , "read");
            if(ret == 0){  // 主动退出
                write(fdw , "我退出啦 , 再见\n" ,30);
                printf("退出 \n");
                break;
            }
            ret = write(fdw , buf , ret); ERROR_CHECK(ret , -1 , "write");
        }  
    }
     close(fdr);close(fdw);
}


//./qiang 1.pipe 2.pipe  //IO 多路复用  // 阿强超时， 踢出  // 刷新时间戳
void test3(int argc , char * argv[]){
    ARGS_CHECK(argc ,3);
    int fdw = open(argv[1] , O_WRONLY);
    ERROR_CHECK(fdw , -1 , "open");
    int fdr = open(argv[2] , O_RDONLY);
    ERROR_CHECK(fdr , -1, "open");
    printf("aqinag is connected \n");
    char buf[4096] = {0};
    ssize_t ret = 0;
    fd_set rdset; // fd_set 申请内存
    struct timeval timeout;
    while(1){  // 每次循环开始 重置监听集合  
        FD_ZERO(&rdset); // 清零 ， rdset 最开始是监听集合
        FD_SET(STDIN_FILENO , & rdset);
        FD_SET(fdr , & rdset);
 
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;

        ret = select(fdr+1 , &rdset , NULL , NULL , &timeout);
        ERROR_CHECK(ret , -1 , "select");
        //select 返回说明 ， fdr or stdin 中有一个就绪了， rdset  是就绪集合
        // if(ret == 0){
        //     printf("timeout \n");
        //     time_t now = time(NULL);
        //     printf("%s \n" , ctime(&now));
        //     continue;
        // }

        if(FD_ISSET(fdr , &rdset)){    // 是否管道就绪
            memset(buf , 0 , sizeof(buf));
            ret =  read(fdr , buf , sizeof(buf));  ERROR_CHECK(ret , -1 , "read");
            if(ret == 0){
                printf("对方关闭 ,  退出\n");
                break;
            }
            printf("             azhen :  %s",  buf);
        }

        if(FD_ISSET(STDIN_FILENO , &rdset)){
            memset(buf , 0 , sizeof(buf));
            ret = read(STDIN_FILENO , buf , sizeof(buf));  ERROR_CHECK(ret , -1 , "read");
            if(ret == 0){  // 主动退出
                write(fdw , "我退出啦 , 再见\n" ,30);
                printf("退出 \n");
                break;
            }
            ret = write(fdw , buf , ret); ERROR_CHECK(ret , -1 , "write");
        }  
    }
     close(fdr);close(fdw);
}


//./qiang 1.pipe 2.pipe  //IO 多路复用  // 阿强超时， 踢出  // 使用固定时间戳 ，可以踢多人
void test4(int argc , char * argv[]){
    ARGS_CHECK(argc ,3);
    int fdw = open(argv[1] , O_WRONLY);
    ERROR_CHECK(fdw , -1 , "open");
    int fdr = open(argv[2] , O_RDONLY);
    ERROR_CHECK(fdr , -1, "open");
    printf("aqinag is connected \n");
    char buf[4096] = {0};
    ssize_t ret = 0;
    fd_set rdset; // fd_set 申请内存
    struct timeval timeout;
    while(1){  // 每次循环开始 重置监听集合  
        FD_ZERO(&rdset); // 清零 ， rdset 最开始是监听集合
        FD_SET(STDIN_FILENO , & rdset);
        FD_SET(fdr , & rdset);
 
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;

        ret = select(fdr+1 , &rdset , NULL , NULL , &timeout);
        ERROR_CHECK(ret , -1 , "select");

        if(FD_ISSET(fdr , &rdset)){    // 是否管道就绪
            memset(buf , 0 , sizeof(buf));
            ret =  read(fdr , buf , sizeof(buf));  ERROR_CHECK(ret , -1 , "read");
            if(ret == 0){
                printf("对方关闭 ,  退出\n");
                break;
            }
            printf("             azhen :  %s",  buf);
        }

        if(FD_ISSET(STDIN_FILENO , &rdset)){
            memset(buf , 0 , sizeof(buf));
            ret = read(STDIN_FILENO , buf , sizeof(buf));  ERROR_CHECK(ret , -1 , "read");
            if(ret == 0){  // 主动退出
                write(fdw , "我退出啦 , 再见\n" ,30);
                printf("退出 \n");
                break;
            }
            ret = write(fdw , buf , ret); ERROR_CHECK(ret , -1 , "write");
        }  
    }
     close(fdr);close(fdw);
}


int main(int argc , char * argv[]){
   test4(argc , argv);
}


