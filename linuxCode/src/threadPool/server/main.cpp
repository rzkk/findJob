#include "threadPool.h"





int epollAdd(int epfd , int fd){
    struct epoll_event events;
    events.events = EPOLLIN;
    events.data.fd = fd;
    epoll_ctl(epfd , EPOLL_CTL_ADD , fd, &events);
    return 0;
}
int epollDel(int epfd , int fd){
    epoll_ctl(epfd , EPOLL_CTL_DEL , fd, NULL);
    return  0;
}

int tcpInit(const char * ip , const char * port , int *psockfd){

    *psockfd = socket(AF_INET , SOCK_STREAM , 0);

    int reuse = 1;
    int ret =  setsockopt(*psockfd, SOL_SOCKET , SO_REUSEADDR , &reuse , sizeof(reuse));
    errorEqualCheck(ret ,-1 , "setsockopt");

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ip);

    ret = bind(*psockfd , (struct sockaddr*)(&addr), sizeof(addr));
    errorEqualCheck(ret ,-1 , "bind");
    listen(*psockfd , 50);
    return 0;
}

int exitpipe[2]; //要在信号处理函数中处理
void handler(int signum ){
    write(exitpipe[1] , "1",1);
}
int main(int argc ,char * argv[]){
    //./serverTest 172.22.15.140 1234 3
    argsCheck(argc , 4);

    pipe(exitpipe);
    if(fork() != 0){
        close(exitpipe[0]);
        signal(SIGUSR1,handler);
        wait(NULL);
        printf("exit \n");
        exit(0);
    }
    close(exitpipe[1]); //子进程管写
    threadPool_t threadpool;
    threadPollInit(&threadpool , atoi(argv[3]));
    
    int sockfd;
    tcpInit( argv[1] , argv[2] ,&sockfd);

     //初始化 epoll
    int epfd = epoll_create(1);
    epollAdd(epfd , sockfd);
    epollAdd(epfd , exitpipe[0]);
   
    while(1){
        struct epoll_event readSet[1024];
        int readNum = epoll_wait(epfd , readSet , 1024 ,-1);
        
        for(int i =0; i< readNum ;++i){
            if(readSet[i].data.fd == sockfd){ // 如果就绪的是sockfd 说明是网络连接来了
                int netfd = accept(sockfd , NULL,NULL);
                printf("one client connected \n");
                //分配
                pthread_mutex_lock(&threadpool.mutex);
                enQueue(&threadpool.taskQueue,netfd);
                pthread_cond_signal(&threadpool.cond);
                pthread_mutex_unlock(&threadpool.mutex);
                //close(netfd);
            }else  if(readSet[i].data.fd == exitpipe[0]){

                printf("threadpool is going to exit\n");

                pthread_mutex_lock(&threadpool.mutex);
                threadpool.exitflag = 1;
                pthread_cond_broadcast(&threadpool.cond); // 需要子线程从wait 醒来
                pthread_mutex_unlock(&threadpool.mutex);
                
                // for(int j =0; j<threadpool.tidArr.workNum ;++j){
                //     pthread_cancel(threadpool.tidArr.arr[j]);
                // }
                for(int j =0; j<threadpool.tidArr.workNum ;++j){
                    pthread_join(threadpool.tidArr.arr[j],NULL);
                }
                exit(0);
            }
        }
  
    }
}