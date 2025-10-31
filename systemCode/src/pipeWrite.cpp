#include"func.h"

void test1( int argc , char * argv[]){  // 写pipe
    ARGS_CHECK(argc,2);
    int fdw = open(argv[1] , O_WRONLY);
    ERROR_CHECK(fdw , -1 , "open");
    printf("write side is opened \n");
    sleep(5);
    write(fdw , "hello" , 5);
    close(fdw);
    printf("write tuichu\n");
}

void test2( int argc , char * argv[]){  // 全双工
    ARGS_CHECK(argc,3);
    int fdw1 = open(argv[1] , O_WRONLY);
    int fdr2 = open(argv[2] , O_RDONLY);
    ERROR_CHECK(fdw1 , -1 , "open");
    ERROR_CHECK(fdr2 , -1 , "open");
    printf("write side is opened \n");
   
    //write(fdw , "hello" , 5);
    close(fdw1);
    close(fdr2);
    printf("write tuichu\n");
}

void test3(int argc , char * argv[]){ //重定向 + 管道
    ARGS_CHECK(argc,2 );
    int fd = open(argv[1] , O_WRONLY);
    ERROR_CHECK(fd , -1 , "open");

    printf("hello world  1 \n");
    dup2(STDOUT_FILENO , 10);

    dup2(fd , STDOUT_FILENO);

    printf("hello world 2 \n");
    //write(fd , "hello" , 5);

    dup2(10 , STDOUT_FILENO);

    printf("hello world 3 \n");

    close(fd);
}


void test4(int argc , char * argv[]){   //全双工
    ARGS_CHECK(argc , 3);

    int fdw = open(argv[1] , O_WRONLY);
    ERROR_CHECK(fdw , -1, " open");

    int fdr = open(argv[2] , O_RDONLY);
    ERROR_CHECK(fdr , -1, " open");
    // char buf[1024] = {0};
    // ssize_t ret =  read(fdr , buf , sizeof(buf));
    // ERROR_CHECK(ret , -1 , "read");
    // printf("%d  %s", ret , buf);
    printf("aqiang is connected \n");
    close(fdr);
    close(fdw);
} 

void test5(int argc , char * argv[]){   //全双工
    ARGS_CHECK(argc , 3);

    int fd = open(argv[1] , O_WRONLY);
    ERROR_CHECK(fd , -1, " open");

    char buf[4096] = {0};
    int cnt = 0;

    while(1){
        write(fd , buf , sizeof(buf));
        printf("write one  %d \n",cnt++);
    }




    close(fd);
} 



int main(int argc , char * argv[]){
    test5(argc , argv);
}


