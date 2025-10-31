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

void test5(int argc , char * argv[]){   //全双工
    ARGS_CHECK(argc , 2);

    int fd = open(argv[1] , O_RDONLY);      
    ERROR_CHECK(fd , -1, " open");

    
    char buf[4096];
    sleep(10);

    while(1){
        read(fd , buf , 4096);
        printf("read one\n")  ;
        sleep(2);
    }


    close(fd);
    
} 


int main(int argc , char * argv[]){
    test5(argc , argv);
}