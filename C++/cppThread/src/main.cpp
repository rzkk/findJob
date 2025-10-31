#include<iostream>
#include<thread>

using std::cout;
using std::endl;
using std::thread;

#if 0
// 传普通函数
void threadFunc1(int x  ){
    cout<<x<<endl;
    cout<<"child tid " << std::this_thread::get_id()<<endl;
}

void test1(){
    thread th(threadFunc1 , 1);

    cout<<"child tid " << th.get_id()<<endl;

    th.join();
}

//传函数指针
void threadFunc2(int x  ){
    cout<<x<<endl;
    cout<<"child threadFunc2 ;"<<endl;
}
void test2(){
    typedef void (*pFunc)(int);  // pFunc 函数指针
    pFunc f = threadFunc2;      
    thread th(f , 1);

    th.join();
}
#endif
#if 0
//传函数引用
void threadFunc1(int x  ){
    cout<<x<<endl;
    cout<<"child tid " << std::this_thread::get_id()<<endl;
    cout<<"child threadFunc2 ;"<<endl;

}

void test1(){
    typedef void (&pFunc)(int);  // pFunc 函数引用
    pFunc f = threadFunc1;      
    thread th(f , 1);

    th.join();
}


#endif

#if 0
//函数对象
class Example
{
public:
    void operator()(int x){
        cout<<x<<endl;
        cout<<"child tid " << std::this_thread::get_id()<<endl;
        cout<<"child operator() ;"<<endl;
    }
};
void test1(){
    Example ex;
    thread th(ex , 4);
    th.join();
}
#endif
#if 0
#include<functional>
//传lambda 
void test1(){
    thread th( [](int x ){
        cout<<x<<endl;
        cout<<"child tid " << std::this_thread::get_id()<<endl;
        cout<<"child lambda () ;"<<endl;
        } , 4);
    th.join();
}
//传function
void test2(){
    std::function<void(int)>f = [](int x ){
        cout<<x<<endl;
        cout<<"child tid " << std::this_thread::get_id()<<endl;
        cout<<"child function () ;"<<endl;
        } ;
    thread th(f, 4);
    th.join();
}

void threadFunc(int x  ){
    cout<<x<<endl;
    cout<<"child tid " << std::this_thread::get_id()<<endl;
    cout<<"child bind ;"<<endl;

}
void test3(){

    thread th(std::bind(threadFunc,5));
    th.join();
}
#endif

#if 0// mutex 
#include<mutex>
int gCnt = 0;
std::mutex mtx;
void threadFunc( ){
    for(size_t idx = 0; idx < 10000000; ++idx ){
        mtx.lock();
        ++gCnt;
        mtx.unlock();
    }
    
}
void test1(){
    thread th(threadFunc);

    for(size_t idx = 0; idx < 20000000; ++idx ){
        mtx.lock();
        ++gCnt;
        mtx.unlock();
    }
    
    th.join();
    cout<<gCnt<<endl;
}
#endif 

#if 0// mutex 
#include<mutex>
using std::mutex;
int gCnt = 0;
std::mutex mtx;
class MutexLockGuard{
public: 
    MutexLockGuard(mutex &mtx):_mtx(mtx){
        _mtx.lock();
    }

    ~MutexLockGuard(){
        _mtx.unlock();
    }
private:
    std::mutex &_mtx;
};

void threadFunc( ){
    for(size_t idx = 0; idx < 10000000; ++idx ){
        //mtx.lock();
        MutexLockGuard autolock(mtx);
        ++gCnt;
        //mtx.unlock();
    }
    
}
void test1(){
    thread th(threadFunc);

    for(size_t idx = 0; idx < 20000000; ++idx ){
        //mtx.lock();
        MutexLockGuard autolock(mtx);
        ++gCnt;
       // mtx.unlock();
    }
    
    th.join();
    cout<<gCnt<<endl;
}
#endif 
#if 0 // lock_guard 

#include<mutex>
using std::mutex;
using std::lock_guard;
int gCnt1 = 0;
int gCnt2 = 0;
std::mutex mtx;

void threadFunc( ){
    for(size_t idx = 0; idx < 10000000; ++idx ){
        //mtx.lock();
        {
            lock_guard<mutex> lg(mtx);
            ++gCnt1;
        }
        ++gCnt2;
        //mtx.unlock();
    }
    
}
void test1(){
    thread th(threadFunc);

    for(size_t idx = 0; idx < 20000000; ++idx ){
        //mtx.lock();
        {
            lock_guard<mutex> lg(mtx);
            ++gCnt1;
        }

        ++gCnt2;
        //mtx.unlock();
    }
    
    th.join();
    cout<<gCnt1<<endl;
    cout<<gCnt2<<endl;
}
#endif 
#if 0 // unique_lock 

#include<mutex>
using std::mutex;
using std::unique_lock;
int gCnt1 = 0;
int gCnt2 = 0;
std::mutex mtx;

void threadFunc( ){
    for(size_t idx = 0; idx < 10000000; ++idx ){
        //mtx.lock();
        
        unique_lock<mutex> lg(mtx);
        ++gCnt1;
        lg.unlock();
        
        //.....
        lg.lock();
        ++gCnt2;
        lg.unlock();
        //mtx.unlock();
    }
    
}
void test1(){
    thread th(threadFunc);

    for(size_t idx = 0; idx < 20000000; ++idx ){
        unique_lock<mutex> lg(mtx);
        ++gCnt1;
        lg.unlock();
        
        //.....
        lg.lock();
        ++gCnt2;
        lg.unlock();
        //mtx.unlock();
    }
    
    th.join();
    cout<<gCnt1<<endl;
    cout<<gCnt2<<endl;
}
#endif

#if 1 // atomic

#include<mutex>
#include<atomic>
#include<string.h>
using std::mutex;
using std::atomic;
atomic<int> gCnt1(0);
std::mutex mtx;
class Point{
public:
    Point(int  x , int y):
                _x(x),_y(y){
        
    }
    void print() const {
        cout<<_x <<"  "<<_y<<endl;;
    }
    int & getX(){
        return _x;
    }
    int _x = 0 ,_y = 0;
};

Point p2 =  Point(3,4);
atomic<Point> gCnt3( p2 );

void threadFunc( ){
    for(size_t idx = 0; idx < 10000000; ++idx ){
        //mtx.lock();
        ++gCnt1;
        ++(gCnt3.load().getX());
    }
}
void test1(){
    thread th(threadFunc);

    for(size_t idx = 0; idx < 20000000; ++idx ){
        ++gCnt1;
        ++(gCnt3.load().getX());
    }
   

    cout<<gCnt3.is_lock_free()<<endl;  //判断自定义的类型是不是原子的


    th.join();


    cout<<gCnt3.load()._x<<endl;
   
  
}
#endif
int main(){

    test1();
    return 0;
}


