#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__


#include"func.h"

//枚举状态 
enum {
    FREE,
    BUSY
};
//等价于
// #define FREE 0
// #define BUSY 1

// 记录多少子线程， 以及子线程tid 
typedef struct {
    pthread_t * arr;
    int workNum;
} tidArr_t;

//任务队列的节点

typedef  struct node_s{ //任务队列
    int netfd;
    struct node_s * pNext;
} node_t;
typedef  struct{ //任务队列
    node_t * pFront;
    node_t * pRear;
    int queueSize;
} taskQueue_t;


//所有的子线程的信息
//任务队列信息
//锁
//条件变量
typedef struct {
    tidArr_t tidArr;
    taskQueue_t taskQueue;
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    int exitflag;
} threadPool_t;



int tidArrInit(int workerNum , tidArr_t * workArr);
int taskQueueInit( taskQueue_t *pqueue);
int threadPollInit( threadPool_t * pthreadPoll , int workerNum );

int enQueue(taskQueue_t * pqueue , int netfd  );

int deQueue( taskQueue_t * pqueue  );


//返回值 ： 标识是否出错
// 创建多少个 ， 以及修改每个工人的信息 ， 传入传出
// int makeWorker(int workerNum , workerdata_t * workArr);
// int workLoop(int sockfd);

// //psockfd : 传入传出
// int tcpInit(const char * ip , const char * port , int *psockfd);


// int sendFd(int sockfd , int fdtosend, int exitFlag);
// int recvFd(int sockfd , int* fdtosend, int * pExitFlag);

#endif