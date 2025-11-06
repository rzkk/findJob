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

void test5(int argc , char * argv[]){   //持续写 ， 测试写阻塞
    ARGS_CHECK(argc , 2);

    int fd = open(argv[1] , O_WRONLY);
    ERROR_CHECK(fd , -1, " open");

    char buf[1024] = {0};
    int cnt = 0;

    while(1){
        write(fd , buf , sizeof(buf));
        printf("write one  %d \n",cnt++);
    }




    close(fd);
} 

typedef struct 
{
    unsigned int len = 0;
    char buf[4092] = {0}; 
}Data;

void test7(int argc , char * argv[]){
    ARGS_CHECK(argc , 3);

    int fdw = open(argv[1] , O_WRONLY);
    ERROR_CHECK(fdw , -1 , "open");

    int fdFile = open(argv[2] , O_RDONLY);
    ERROR_CHECK(fdFile , -1 , "open");

    //先发文件名 
    Data data;  // 分两次发
    data.len = strlen(argv[2]);
    memcpy(data.buf , argv[2] ,  data.len);
    cout<<data.buf<<endl;
    int ret = write(fdw , &data.len,  sizeof(data.len));ERROR_CHECK(ret , -1 ,"write");
    ret = write(fdw , data.buf,  data.len );  ERROR_CHECK(ret , -1 ,"write");
  

    //bzero(data.buf , sizeof(data.buf));
    while((ret = read(fdFile , data.buf, sizeof(data.buf))) != 0){
        ERROR_CHECK(ret , -1 , "read");
        data.len = ret ;

        write(fdw , &data.len,  sizeof(data.len));ERROR_CHECK(ret , -1 ,"write");
        write(fdw, data.buf , data.len);ERROR_CHECK(ret , -1 ,"write");

    //    bzero(data.buf , sizeof(data.buf));
    }

    close(fdw);

}

int main(int argc , char * argv[]){
    test7(argc , argv);
}


