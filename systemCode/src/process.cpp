#include"func.h"


namespace ProcessCall{
void test1(){
    printf(" pid = %d  ppid = %d \n" , getpid() , getppid());
}

int dataSeg = 1;   //数据段
void test2(){
    int dataStack = 1; // 栈

    int *pHeap = (int *)malloc(sizeof(int));  // 堆
    *pHeap = 1;


    if(fork()){   // 父亲 
        sleep(3);
        printf("fu %d %d  %d    " ,  dataSeg,  dataStack , *pHeap);


    }else{
        dataSeg += 1;
        dataStack +=1;
        *pHeap += 1; 
        printf("zi %d %d  %d     " ,  dataSeg,  dataStack , *pHeap);
    }
}
void test3(int argc ,char * argv[]){
   
    FILE * fp1 = fopen(argv[1] , "r+");

    fwrite("hello\n" , 6,1,fp1); //全缓冲
    fflush(fp1);
    if(fork()){   // 父亲 
        sleep(3);
        fwrite("world" , 5,1,fp1);;


    }else{
       fwrite("nihao" , 5,1,fp1);
       
    }
}
void test4(){
   
    if(fork()){   // 父亲 
       printf("parent pid = %d  ppid = %d \n" , getpid(), getppid());
        wait(NULL);

    }else{
       sleep(1);
       printf("child  pid = %d  ppid = %d \n" , getpid(), getppid());

    }
}
};

namespace waitTest{
void test(){
    int wstatus;
    if(fork()){
        wait(&wstatus);  //子进程退出后 获取子进程死因
        if(WIFEXITED(wstatus)){  //是否正常退出
            cout<<"exit status = "<<WEXITSTATUS(wstatus)<<endl;  // 子进程正常退出时 的main 返回值
        }else if(WIFSIGNALED(wstatus)){ // 是否异常退出 // 信号杀死的
            cout<<"abnomal quit , terminal signal = "<<WTERMSIG(wstatus)<<endl;
        }
    }else{
        while(1){
            sleep(1);
        }
    }
}

};

void sessionTest(){
    if(fork()){   // 父亲 
       printf("parent pid = %d  ppid = %d  pgid = %d  pgid of ppid = %d   sid = %d\n" , getpid(), getppid(), getpgid(0),getpgid(getppid()),  getsid(0));
       wait(NULL);

    }else{
    setpgid(0,0);   //设置自己为组长  
    printf("child pid = %d  ppid = %d  pgid = %d  pgid of ppid = %d   sid = %d\n" , getpid(), getppid(), getpgid(0),getpgid(getppid()),  getsid(0));
        while(1){
            sleep(1);
        }
    }
}
void Daemon(){
    //新建会话
    if(fork()){
        exit(0);
    }
    setsid();

    //关闭设备
    for(int i = 0 ; i< 64 ;++i){
        close(i);
    }

    chdir("/");
    umask(0);
}

void pipTest(){
    int fds1[2] , fds2[2];
    pipe(fds1);
    pipe(fds2);

    if(fork()){   //父
        close(fds1[0]); 
        close(fds2[1]);
        char buf[4096] = {0};
        //int cnt = 0 ;
        while(1){
            
            write(fds1[1] , buf ,5);
           
            sleep(1);
        }
        

    }else{  // 子
        close(fds1[1]);
        close(fds2[0]);

        //char buf[4096]={0};
        //int cnt = 0;
        // while(1){
        //     int ret = read( fds1[0] ,buf ,4096 );
        //     ERROR_CHECK(ret , -1, "read");
        //     cout<<"        read "<<cnt++ <<endl;
        //     sleep(4);
        // }
       
        sleep(2);
        close(fds1[0]);  // 读关闭
        //cout<<buf<<endl;

    }
}
#define Num 10000000
void shardMemoryTest(){
    int shmid = shmget(IPC_PRIVATE , 4096 , IPC_CREAT|0600);
    ERROR_CHECK(shmid , -1 , "shmget");

    int *p = (int *)shmat(shmid ,NULL , 0 );

    if(fork()){
       
        for(int i = 0 ;i <Num  ;++i){
                ++*p ;
        }
        wait(NULL);
        cout<<*p <<endl;
    }else{
      
        for(int i = 0 ;i <Num  ;++i){
                ++*p ;
        }
        
    }  
}

namespace signalTest{

void handler1(int signum){
    printf(" before %d  \n" , signum);
    sleep(5);
    printf(" after  %d  \n" , signum);
}

void test1(){
    signal(SIGINT , handler1);
    signal(SIGQUIT , handler1);
    while(1){
        sleep(1);
    }
}

void handler2(int signum){
    printf("signum =   %d  \n" , signum);
}

void test2(){  // 测试 重启低速系统调用
    signal(SIGINT , handler2);
    char buf[4096] = {0};
    ssize_t ret = read(STDIN_FILENO , buf  , sizeof(buf));
    ERROR_CHECK(ret , -1, "read");
    printf("%ld     %s  \n" ,ret  ,  buf); 
    
}

void handler3(int signum){  // 一参数
    printf("signum =   %d  \n" , signum);
}
void test3(){  // sigaction 的用法 ： 一参数
    struct sigaction act ;
    memset(&act , 0 , sizeof(act));

    act.sa_handler = handler3;
    act.sa_flags = SA_RESTART;  

    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask , SIGQUIT);


    sigaction(SIGINT  , &act , NULL);
    sigaction(SIGQUIT , &act , NULL);
    while(1){
        sleep(1);
    }
}


void handler5(int signum , siginfo_t * siginfo , void * p ){  // 三参数
    printf("signum =   %d   , uid =   , %s \n" , signum , siginfo->si_uid , p );
}
void test5(){          // sigaction 的用法 ： 三参数 
    struct sigaction act ;
    memset(&act , 0 , sizeof(act));

    act.sa_sigaction = handler5;
    act.sa_flags = SA_SIGINFO| SA_RESTART;  

    //sigemptyset(&act.sa_mask);
    //sigaddset(&act.sa_mask , SIGQUIT);

    sigaction(SIGINT  , &act , NULL);
    sigaction(SIGQUIT , &act , NULL);

    while(1){
        sleep(1);
    }

}


void handler6(int signum  ){  
    printf("before  signum =   %d \n " , signum  );
    sleep(5);
    sigset_t pending;
    sigpending(&pending);  //获取集合

    if(sigismember(&pending , SIGINT)){   // 查集合
        printf("                 sigint is in pending \n");
    }else{
         printf("               sigint is not  in pending\n ");
    }

    printf("after  signum =   %d \n " , signum  );
}
void test6(){          // sigpending  的用法
    
    signal(SIGINT , handler6);
    


    while(1){
        sleep(1);
    }

}


void handler7(int signum  ){  
    printf(" signum =   %d \n " , signum  );
}
void test7(){          //sigpromask  , 屏蔽十秒2号信号
    
    signal(SIGINT , handler7);
    
    sigset_t set;       // 准备一个位图 ， 加入二号
    sigemptyset(&set);
    sigaddset(&set , SIGINT);

    sigprocmask(SIG_BLOCK , &set , NULL);  // 一直在屏蔽
    sleep(5);

    sigset_t pending;   // 看看休眠的过程中 ， 有没有二号信号
    sigpending(&pending);

    if(sigismember(&pending , SIGINT)){   // 查集合
        printf("                 sigint is in pending \n");
    }else{
         printf("               sigint is not  in pending\n ");
    }

    sigprocmask(SIG_UNBLOCK , &set , NULL);  // 解除屏蔽 ， 若有的未决的 会被递送
    sleep(1);
}

void handler8(int signum  ){    
    time_t now = time(NULL);
    printf("now =  %s   \n" , ctime(&now)  );
}
void test8(){         // 定时器 ， setitimer 
    
    signal(SIGALRM , handler8);
    signal(SIGVTALRM , handler8);
    struct itimerval itimer;

    itimer.it_value.tv_sec =1;
    itimer.it_value.tv_usec = 0;

    itimer.it_interval.tv_sec = 3;
    itimer.it_interval.tv_usec = 0;
    
    setitimer(ITIMER_VIRTUAL , &itimer , NULL);
    handler8(0); // 获取当前时间


    while(1){
        int i = 0;
        
        i++;
    }
    
}
}

int main(int argc ,char * argv[]){
    signalTest::test8();
    
    return 0;
    //while(1);
}