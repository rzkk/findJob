
#include "threadPool.h"


typedef struct{
    int length;
    char data[1000]; //可以保存任何数据 //1024 数据上限
}train_t;

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

//发送大火车箱
int transFile3(int netfd ){
    train_t train;
    bzero(&train,sizeof(train));
    char filename[] = "copy.pdf";
    train.length = strlen(filename);
    memcpy(train.data , filename, strlen(filename));
    send(netfd , &train,  sizeof(train.length) +train.length,MSG_NOSIGNAL);

    int fd = open(filename , O_RDWR);
    errorEqualCheck(fd , -1, "open");
    struct stat statbuf ;
    fstat(fd , &statbuf);
    train.length = statbuf.st_size;
    printf("filesi22222ze =  %ld\n",statbuf.st_size );
    // memcpy(train.data , &statbuf.st_size ,train.length);
    // send(netfd , &train,  sizeof(train.length) + train.length,MSG_NOSIGNAL);
    
    //statbuf.st_size 映射区大小 = 文件大小
    char *p = (char *)mmap(NULL ,statbuf.st_size,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0 );
    errorEqualCheck(p,MAP_FAILED,"mmap");

    send(netfd , &train.length,  sizeof(train.length) ,MSG_NOSIGNAL);
    send(netfd , p, train.length ,MSG_NOSIGNAL);

    train.length = 0;
    send(netfd , &train.length,  sizeof(train.length) ,MSG_NOSIGNAL);
    munmap(p,statbuf.st_size);
    return 0;
 }
void unlock(void * arg){
    threadPool_t * pthreadPool = (threadPool_t *)arg;
    pthread_mutex_unlock(&pthreadPool->mutex);
}
void * threadFunc(void * arg){
    threadPool_t* pthreadPool = (threadPool_t*)arg;
    while(1){  // 后事件 , 完成一次之后 会紧接着查询任务队列中有无就绪的
        pthread_mutex_lock(&pthreadPool->mutex);
        int netfd;
        //pthread_cleanup_push(unlock , pthreadPool); // 压栈
        while(pthreadPool->exitflag == 0 &&pthreadPool->taskQueue.queueSize <= 0){
            pthread_cond_wait(&pthreadPool->cond, & pthreadPool->mutex);
        }
        //退出循环 两个条件 ： 来任务了 or  退出了
        if(pthreadPool->exitflag == 1){
            printf("i am child , i am going to exit \n");
            pthread_mutex_unlock(&pthreadPool->mutex);
            pthread_exit(NULL);
        } 
        netfd = pthreadPool->taskQueue.pFront->netfd;
        deQueue(&pthreadPool->taskQueue);
        //pthread_mutex_unlock(&pthreadPool->mutex);
        //pthread_cleanup_pop(1);//弹栈
        //业务
        transFile4(netfd); // 压栈 弹栈 是一对{ } ， 在其中定义的变量属于 局部变量外界不可用
        close(netfd);
    }
}

int makeWorker(threadPool_t * pthreadPoll  ){
    for(int i =0;i<pthreadPoll->tidArr.workNum ;++i){
        pthread_create(&pthreadPoll->tidArr.arr[i] , NULL,threadFunc, pthreadPoll);
    }
    return 0;
}


int tidArrInit( tidArr_t * ptidArr,int workerNum ){
    //pthread_t tid;
    //申请内存，存储每个子线程的tid 
    ptidArr->arr =  (pthread_t *)calloc(workerNum , sizeof(pthread_t));
    ptidArr->workNum = workerNum;

    //makeWorker();
    return 0;
}

//返回值只标识是否正确执行
int enQueue(taskQueue_t * pqueue , int netfd  ){  // 入队
    node_t * pnew = (node_t * )calloc(1,sizeof(node_t));
    pnew->netfd = netfd;
    if(pqueue->queueSize == 0){ //队列为空
        pqueue->pFront = pnew;  //
        pqueue->pRear  = pnew;
    }else{
        pqueue->pRear->pNext = pnew;
        pqueue->pRear = pnew;
    }
    pqueue->queueSize ++;
}
int deQueue( taskQueue_t * pqueue  ){  //出队
    node_t * pCur = pqueue->pFront;
    pqueue->pFront = pCur->pNext;
    if(pqueue->queueSize == 1){
        pqueue->pRear = NULL;
    }
    free(pCur);
    --pqueue->queueSize;
    return 0;
}

int taskQueueInit( taskQueue_t *pqueue){
    bzero(pqueue, sizeof(taskQueue_t));
    return 0;
}


int threadPollInit( threadPool_t * pthreadPoll , int workerNum ){

    tidArrInit(&pthreadPoll->tidArr , workerNum);
    makeWorker(pthreadPoll);
    taskQueueInit( &pthreadPoll->taskQueue );
    pthread_mutex_init(&pthreadPoll->mutex , NULL);
    pthread_cond_init(&pthreadPoll->cond,NULL);
    pthreadPoll->exitflag = 0; //
    return 0;
}



// int workLoop(int sockfd){
//     while(1){
//         int netfd;
//         int exitflag;
//         recvFd(sockfd , &netfd , &exitflag); //接收任务
//         if(exitflag ==1){
//             printf("I am going to exiting \n");
//             exit(0);
//         }
//         printf("begin work \n");//执行任务

//         transFile3(netfd);

//         printf("end work \n");
//         //任务完成之后 ，向主人进程发送自己的PID 
//         //sleep(10);
//         pid_t pid = getpid();
//         if(pid == 0){
//             printf("----------------------70707707070\n");
//         }
//         send( sockfd , &pid ,sizeof(pid),0  ); //sockfd socketpair的

//         close(netfd);   
//         printf("----------------------333333\n");
//         //sendFd 中的sendmsg 是传内核数据结构的
//         //父子之间的不同通信 ， 发个数据之类的之间从socketpair 的send 就是
//     }
// }
