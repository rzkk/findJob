#include "processPool.h"


int sendFd(int sockfd , int fdtosend, int exitFlag){
    struct msghdr hdr;
    bzero(&hdr , sizeof(hdr));//msg_name  = NULL  msg_namelen = 0;
    //无论正文有没有用，但是必须要有
    //char buf[] = "hello";
    struct iovec vec[1];   //这是正文
    vec[0].iov_base = &exitFlag;  // 正文部分 , 第一个离散碎片首地址
    vec[0].iov_len = sizeof(exitFlag);     

    hdr.msg_iov = vec;      //离散区域的信息 放在hdr 中
    hdr.msg_iovlen = 1;
    //控制字段 ， 记录要发送的内核信息                    data ： fd : int
    struct cmsghdr * pcmsg = (struct cmsghdr*) malloc(CMSG_LEN(sizeof(int)));
    pcmsg->cmsg_len = CMSG_LEN(sizeof(int));
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;
    *(int *) CMSG_DATA(pcmsg) = fdtosend; //CMSG_DATA 得到data首地址

    hdr.msg_control = pcmsg;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));

    int ret = sendmsg(sockfd , &hdr ,0);
    errorEqualCheck(ret ,-1 ,0);

    return 0;
}

int recvFd(int sockfd , int * pfdtorecv , int *exitFlag ){
    //接收和发送的区别 ， 接收方不知道 buf 和 pcmsg->data的内容
    struct msghdr hdr;
    bzero(&hdr , sizeof(hdr));//msg_name  = NULL  msg_namelen = 0;
    //无论正文有没有用，但是必须要有
    char buf[6] = {0};
    struct iovec vec[1];   //这是正文
    vec[0].iov_base = exitFlag;  // 正文部分 , 第一个离散碎片首地址
    vec[0].iov_len = sizeof(*exitFlag);     

    hdr.msg_iov = vec;      //离散区域的信息 放在hdr 中
    hdr.msg_iovlen = 1;
    //控制字段 ， 记录要发送的内核信息                    data ： fd : int
    struct cmsghdr * pcmsg = (struct cmsghdr*) malloc(CMSG_LEN(sizeof(int)));
    pcmsg->cmsg_len = CMSG_LEN(sizeof(int));
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;    //确定发来的是文件描述符
    //*(int *) CMSG_DATA(pcmsg) = pfdtorecv; //CMSG_DATA 得到data首地址

    hdr.msg_control = pcmsg;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));

    int ret = recvmsg(sockfd , &hdr ,0);
    errorEqualCheck(ret ,-1 ,0);

    *pfdtorecv = *(int*)CMSG_DATA(pcmsg);
    //printf("%d \n", * pfdtorecv); 
    return 0;
}