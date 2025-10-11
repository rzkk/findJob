#include "processPool.h"





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
int exitpipe[2];
void handler(int signum){
    printf("signum = % d \n",signum);
    write(exitpipe[1] , "1",1);
}
int main(int argc ,char * argv[]){
    //./serverTest 172.22.15.140 1234 3
    argsCheck(argc , 4);

    int workNum = atoi(argv[3]);
    workerdata_t workArr[workNum];
    makeWorker(3, workArr);

    signal(SIGUSR1, handler);
    //创建一个自己和自己通信的管道
    pipe(exitpipe);



    int sockfd;
    tcpInit( argv[1] , argv[2] ,&sockfd);

    //初始化 epoll
    int epfd = epoll_create(1);
    epollAdd(epfd , sockfd);
    //监听每个子进程管道的pipesocketfd 
    for(int i =0;i< workNum; ++i){
        epollAdd(epfd, workArr[i].pipesocketfd);
    }
    epollAdd(epfd ,exitpipe[0]);
    while(1){
        struct epoll_event readSet[1024];
        int readNum = epoll_wait(epfd , readSet , 1024 ,-1);

        for(int i =0; i< readNum ;++i){
            if(readSet[i].data.fd == sockfd){ // 如果就绪的是sockfd 说明是网络连接来了
                int netfd = accept(sockfd , NULL,NULL);
                printf("one client connected \n");
                for(int j =0;j< workNum;++j){   //找到之后 退出 ， 没有找到也退出
                    if(workArr[j].status == FREE){
                        sendFd( workArr[j].pipesocketfd, netfd , 0);
                        workArr[j].status = BUSY;
                        break;
                    }
                }
                close(netfd);   //如果以及分配上了， 那么就会有两个netfd指向同一个连接，关父亲的，还有孩子的
                                //如果没有分配上， 说明进程没了， 直接关了
            }else if(readSet[i].data.fd == exitpipe[0]){
                    //进程池要退出了
                    for(int j =0;j< workNum;++j){   //找到之后 退出 ， 没有找到也退出
                       //kill(workArr[j].pid , SIGKILL);
                       sendFd(workArr[j].pipesocketfd , 0, 1);
                       printf("kill pid = %d \n" ,workArr[j].pid  );
                    }
                    for(int j =0;j<workNum ;++j){
                        wait(NULL); //等第一个退出的孩子
                    }
                    printf("All worker died \n");
                    exit(0);
            }
            else { // 工人完成之后 会发个消息回来
                int pipesockfd = readSet[i].data.fd;
                //顺序查找对应的是哪个子进程
                for(int j =0; j < workNum ;++j){   //修改进程状态
                    if(workArr[j].status != FREE && workArr[j].pipesocketfd == pipesockfd){
                        pid_t pid;
                        
                        recv(pipesockfd , &pid, sizeof(pid) , 0); //接收子进程发来的自己pid，有点多余 
                        if(pid == 0) {
                            printf("error \n ");
                            sleep(10);
                        }
                        printf("%d  worker , pid = %d \n", j , pid);
                        workArr[j].status = FREE;    //
                        break;
                    }
                }
            }
        }
    }

}