#include"func.h"


namespace pthread{
void  * routine(void * argv){
   while(1){
        sleep(1);
   }
    //return (void * )0;
}
void test1(){

    //pthread_t tid ; // 将用来获取子线程的  tid 
    int cnt  = 0;
   
    while(1){
        pthread_t tid ; // 将用来获取子线程的  tid 

        int ret = pthread_create(&tid , NULL, routine , NULL);
        THREAD_ERROR_CHECK(ret  , "pthread_create");
        cnt ++;
        if(ret != 0 ) break;
    }
   
    //sleep(1);
}
}

int main(){
    pthread::test1();
    return 0;
}