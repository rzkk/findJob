#ifndef __PROCESS_POOL_H__
#define __PROCESS_POOL_H__


#include"func.h"

//枚举状态 
enum {
    FREE,
    BUSY
};
//等价于
// #define FREE 0
// #define BUSY 1
//工人进程的信息
typedef struct {
    pid_t pid;
    int status;
    int pipesocketfd;    // 父子间通信的文件描述符 socketpair 
} workerdata_t;

//返回值 ： 标识是否出错
// 创建多少个 ， 以及修改每个工人的信息 ， 传入传出
int makeWorker(int workerNum , workerdata_t * workArr);
int workLoop(int sockfd);

//psockfd : 传入传出
int tcpInit(const char * ip , const char * port , int *psockfd);


int sendFd(int sockfd , int fdtosend, int exitFlag);
int recvFd(int sockfd , int* fdtosend, int * pExitFlag);

#endif