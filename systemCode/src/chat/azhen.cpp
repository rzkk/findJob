#include "func.h"

//./zhen 1.pipe 2.pipe
void test1(int argc , char * argv[]){
    ARGS_CHECK(argc ,3);

    int fdr = open(argv[1] , O_RDONLY);
    ERROR_CHECK(fdr , -1 , "open");

    int fdw = open(argv[2] , O_WRONLY);
    ERROR_CHECK(fdw , -1, "open");

    printf("azhen is connected \n");

    char buf[4096] = {0};
    ssize_t ret = 0;
    while(1){
        memset(buf , 0 , sizeof(buf));
        ret =  read(fdr , buf , sizeof(buf));
        ERROR_CHECK(ret , -1 , "read");

        printf("           aqiang :  %s  " ,  buf);

        memset(buf , 0 , sizeof(buf));
       
        ret = read(STDIN_FILENO , buf , sizeof(buf));
        ERROR_CHECK(ret , -1 , "read");

        ret = write(fdw , buf ,ret);
        ERROR_CHECK(ret , -1 , "write");
    }
}


//./zhen 1.pipe 2.pipe   //IO 多路复用
void test2(int argc , char * argv[]){
    ARGS_CHECK(argc ,3);
    int fdr = open(argv[1] , O_RDONLY);
    ERROR_CHECK(fdr , -1 , "open");
    int fdw = open(argv[2] , O_WRONLY);
    ERROR_CHECK(fdw , -1, "open");
    printf("azhen is connected \n");
    char buf[4096] = {0};
    ssize_t ret = 0;
    fd_set rdset; // fd_set 申请内存
    struct timeval timeout;
    while(1){

        FD_ZERO(&rdset); // 清零 ， rdset 最开始是监听集合 
        FD_SET(STDIN_FILENO , & rdset);
        FD_SET(fdr , & rdset);
        
        timeout.tv_sec = 3;   // 3秒
        timeout.tv_usec = 0;

        ret =select(fdr+1 , &rdset , NULL , NULL , NULL);
        ERROR_CHECK(ret , -1 , "select");
        if(ret == 0){   // 判断是否 超时
            printf("timeout \n");
            time_t now = time(NULL);    //获取当前时间
            printf("%s \n" , ctime(&now));  // 转日历时间
            continue;
        }


        if(FD_ISSET(fdr , &rdset)){  // 是否管道就绪  // 阿强来消息啦
            memset(buf , 0 , sizeof(buf));
            ret =  read(fdr , buf , sizeof(buf)); ERROR_CHECK(ret , -1 , "read");
            if(ret == 0){
                printf("对方关闭 ,  退出\n");
                break;
            }
            printf("           aqiang :  %s" ,  buf);
        }
        if(FD_ISSET(STDIN_FILENO , &rdset)){
            memset(buf , 0 , sizeof(buf));
            ret = read(STDIN_FILENO , buf , sizeof(buf));ERROR_CHECK(ret , -1 , "read");
            if(ret == 0){  // 主动退出
                write(fdw , "我退出啦 , 再见\n" ,30);
                printf("退出 \n");
                break;
            }
            ret = write(fdw , buf ,ret);  ERROR_CHECK(ret , -1 , "write");
        }  
    }
     close(fdr);close(fdw);
}



//./zhen 1.pipe 2.pipe   //IO 多路复用   // 阿强超时， 踢出  // 刷新时间戳
void test3(int argc , char * argv[]){
    ARGS_CHECK(argc ,3);
    int fdr = open(argv[1] , O_RDONLY);
    ERROR_CHECK(fdr , -1 , "open");
    int fdw = open(argv[2] , O_WRONLY);
    ERROR_CHECK(fdw , -1, "open");
    printf("azhen is connected \n");
    char buf[4096] = {0};
    ssize_t ret = 0;
    fd_set rdset; // fd_set 申请内存
    struct timeval timeout;
    
    timeout.tv_sec = 10;   // 3秒
    timeout.tv_usec = 0;
    while(1){

        FD_ZERO(&rdset); // 清零 ， rdset 最开始是监听集合 
        FD_SET(STDIN_FILENO , & rdset);
        FD_SET(fdr , & rdset);
        
        ret =select(fdr+1 , &rdset , NULL , NULL , &timeout);
        ERROR_CHECK(ret , -1 , "select");
        if(ret == 0){   // 判断是否 超时
            printf("qiangqiang timeout \n");
            time_t now = time(NULL);    //获取当前时间
            printf("%s \n" , ctime(&now));  // 转日历时间
            
            write(fdw , "你不在， 我就退出啦 , 再见\n" ,40);
            break;
        }


        if(FD_ISSET(fdr , &rdset)){  // 是否管道就绪  // 阿强来消息啦
            memset(buf , 0 , sizeof(buf));
            time_t now = time(NULL);    //获取当前时间
            //printf("%s \n" , ctime(&now));  // 转日历时间
            ret =  read(fdr , buf , sizeof(buf)); ERROR_CHECK(ret , -1 , "read");
            if(ret == 0){
                printf("对方关闭 ,  退出\n");
                break;
            }

            timeout.tv_sec = 10;   // 刷新阿强时间戳
            timeout.tv_usec = 0;
            printf("           aqiang :  %s   %s " ,  buf,ctime(&now));
        }
        if(FD_ISSET(STDIN_FILENO , &rdset)){
            memset(buf , 0 , sizeof(buf));
            ret = read(STDIN_FILENO , buf , sizeof(buf));ERROR_CHECK(ret , -1 , "read");
            if(ret == 0){  // 主动退出
                write(fdw , "我退出啦 , 再见\n" ,30);
                printf("退出 \n");
                break;
            }
            ret = write(fdw , buf ,ret);  
            ERROR_CHECK(ret , -1 , "write");
        }  
    }
    close(fdr);close(fdw);
}


//./zhen 1.pipe 2.pipe   //IO 多路复用   // 阿强超时， 踢出  // // 使用固定时间戳  ， 可以踢多人
void test4(int argc , char * argv[]){
    ARGS_CHECK(argc ,3);
    int fdr = open(argv[1] , O_RDONLY);
    ERROR_CHECK(fdr , -1 , "open");
    int fdw = open(argv[2] , O_WRONLY);
    ERROR_CHECK(fdw , -1, "open");
    printf("azhen is connected \n");
    char buf[4096] = {0};
    ssize_t ret = 0;
    fd_set rdset; // fd_set 申请内存
    struct timeval timeout;
    
    time_t aqianglast = time(NULL);

    while(1){

        FD_ZERO(&rdset); // 清零 ， rdset 最开始是监听集合 
        FD_SET(STDIN_FILENO , & rdset);
        FD_SET(fdr , & rdset);
        timeout.tv_sec = 1;   // 每秒钟就绪一次 ，检查阿强是否超时
        timeout.tv_usec = 0;
        ret =select(fdr+1 , &rdset , NULL , NULL , &timeout);
        ERROR_CHECK(ret , -1 , "select");

        //if(ret == 0 ){   // 判断是否 超时
        time_t now = time(NULL);    //获取当前时间
        if(difftime(now , aqianglast) > 10){
            write(fdw , "你不在， 我就退出啦 , 再见\n" ,40);
            printf("%s \n" , ctime(&now));  // 转日历时间
            break;
        }          
            
       // }


        if(FD_ISSET(fdr , &rdset)){  // 是否管道就绪  // 阿强来消息啦
            memset(buf , 0 , sizeof(buf));
            aqianglast = time(NULL);    //获取当前时间
            ret =  read(fdr , buf , sizeof(buf)); ERROR_CHECK(ret , -1 , "read");
            if(ret == 0){
                printf("对方关闭 ,  退出\n");
                break;
            }
            printf("               %s                   aqiang :  %s" , ctime(&aqianglast), buf  );
        }
        if(FD_ISSET(STDIN_FILENO , &rdset)){
            memset(buf , 0 , sizeof(buf));
            ret = read(STDIN_FILENO , buf , sizeof(buf));ERROR_CHECK(ret , -1 , "read");
            if(ret == 0){  // 主动退出
                write(fdw , "我退出啦 , 再见\n" ,30);
                printf("退出 \n");
                break;
            }
            ret = write(fdw , buf ,ret);  
            ERROR_CHECK(ret , -1 , "write");
        }  
    }
    close(fdr);close(fdw);
}
int main(int argc , char * argv[]){
    test4(argc , argv);
}