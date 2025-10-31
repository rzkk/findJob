/*
 * @Author: rzk ruanzk2098@gmial.com
 * @Date: 2025-01-22 23:52:07
 * @LastEditors: rzk ruanzk2098@gmial.com
 * @LastEditTime: 2025-01-23 17:17:26
 * @FilePath: /cplusplus/src/template.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include<iostream>

using std::cout;
using std::endl;
#if 0

template<class T>
T add(T t1 , T t2){
    return t1 +t2;
}

void test(){
    int    i1 = 1, i2 = 2;
    double d1 = 3.3 , d2 = 4.4;
    cout<<"a + b " <<  add(i1,i2)<<endl;
    //cout<<"d1 + d2 " <<add(i1,d2)<<endl;
    cout<<add<int>(d1,i1)<<endl;
}
#endif

#if 0

template<class T>
T add(T t1 , T t2){
    cout<<"template<class T>  ";
    return t1 +t2;
}

template<class T1 , class T2>
T1 add(T1 t1 , T2 t2){
    cout<<"template<class T1 , class T2>  ";
    return t1 +t2;
}

void test(){
    int    i1 = 1, i2 = 2;
    double d1 = 30.3 , d2 = 40.4;
    cout<<add(i1,i2)<<endl;

    cout<<add(i1,d1)<<endl;
    cout<<add(d1,i1)<<endl;

    cout<<add<int>(d1,i1)<<endl; //template<class T> 
    cout<<add<int>(i1,d1)<<endl; //template<class T1 , class T2>
}
#endif
#if 0

template<class T>
T add(T t1 , T t2){
    cout<<"模板一   "<<endl;;
    return t1 +t2;
}

template<class T1, class T2>
T1 add(T1 t1 , T2 t2){
    cout<<"模板二   "<<endl;;
    return t1 +t2;
}

template<class T1, class T2>
T1 add(T2 t2 , T1 t1){
    cout<<"模板三   "<<endl;;
    return t1 +t2;
}


void test(){
    int a = 10;
    double d = 1.2;
    //add(a,d);
    add<double>(a,d);  //三

    add<int>(a,d);     //二

    add<double>(d,a); // 二

    add<int>(d,a);    // 三
}
#endif

#if 0
#include "myTemplateAdd"
#include<vector>

void test(){
    int a1 = 10 , a2 = 10;

    cout<<add(a1,a2)<<endl;;
    //function();
}

#endif

#if 0
#include<string>
#include<string.h>
using std::string;
template<class T>
T add(T t1 , T t2){
    return t1 + t2;

}
//定义普通函数 ， 优先级更高
// const char * add(const char * t1 , const char *t2  ){
//     char *temp = new char[strlen(t1) + strlen(t2) +1]();
//      strcpy(temp, t1 );
//      strcat(temp, t2);    //拼接
//      return temp;
// }

//这种形式就可以， 
// template<>  // 告诉编译器这里是一个模板
// const char * add(const char * t1 , const char *t2  ){
//     char *temp = new char[strlen(t1) + strlen(t2) +1]();
//      strcpy(temp, t1 );
//      strcat(temp, t2);    //拼接
//      return temp;
// }

template<>  
const char * add<const char *>(const char * t1 , const char *t2  ){
    char *temp = new char[strlen(t1) + strlen(t2) +1]();
     strcpy(temp, t1 );
     strcat(temp, t2);    //拼接
     return temp;
}

void test(){
    const char * pstr1 = " hello "; // 文字常量区 ， OS 管理
    const char * pstr2 = " word ";
    //cout<<add(string(pstr1) , string(pstr2))<<endl;;
    const char * p = add(pstr1 , pstr2);
    cout<<p<<endl;
    delete []p;

}

#endif 


#if 0

template<class T1 ,class T2 , class T3>
T1 add(T2 t1 , T3 t2){
    return t1 + t2;
}



void test(){
    int a = 5;
    double b = 5.3;
    cout<<add<double>(a,b)<<endl;
}

#endif 

#if 0

template<class T = int ,int key = 10>
T multiply(T t1 , T t2){
    return t1 * t2 * key;
}

template<class T1 = double  , class T2 , class  T3  >
T1 add(T2 x , T3 y){
    return x + y;
}


void test(){
    int i1 = 4 , i2 = 3;
    cout<< multiply<int , 10>(i1, i2)<<endl;;
    cout<< multiply(i1, i2)<<endl;;

    cout<< multiply(1.2, 1.2)<<endl;;      //推导
    cout<< multiply<double>(1.2, 1.2)<<endl;;  //指定

    cout<<add(1,2)<<endl;;
} 

#endif 

#if 0 

class Point{
public: 
    Point(double x , double y):_x(x), _y(y){}

    template<class T = int>
    T convert(){
        return (T) (_x+ _y);
    }
    template<class T>
    T fun(T x , T y){
        return x + y ;
    }
private :
    int _x , _y;
};

void test(){
    Point p(1.1,2.2);

    cout<<p.convert()<<endl;;
    cout<<p.convert<int>()<<endl;;
    p.fun(1,2);
}
#endif

#if 0
#include<string>
using std::string;

template<class T = int,int Kcapacity = 10>
class Stack{
public:
    Stack():_top(-1),_data(new T[Kcapacity]()){
        cout<<"Stack()"<<endl;
    }

    ~Stack(){
        if(_data){
            delete[] _data;
            _data = nullptr;
        }
        cout<<"~Stack"<<endl;
    }
    bool empty()const ;
    bool full() const;

    void push(const T &);
    void pop();
    T top();
private:
    int _top;
    T*_data;
};

template<class T , int Kcapacity>
bool Stack<T , Kcapacity>::empty() const{
    return _top == -1;
}

template<class T , int Kcapacity>
bool Stack<T , Kcapacity>::full() const{
    return _top == Kcapacity-1;
}

template<class T , int Kcapacity>
void Stack<T , Kcapacity>::push(const T& x) {
    if(!full()){
        _data[++top] = x;
    }else{
        cout<<"满栈";
    }   
}

template<class T , int Kcapacity>
void Stack<T , Kcapacity>::pop() {
    if(empty()){
        cout<<"空栈";
    }else{
        --_top;
    }   
}

template<class T , int Kcapacity>
T Stack<T , Kcapacity>::top() {
    return _data[_top];
}

void test(){
    Stack<string ,20>ss;
    Stack<int>st;
    Stack<>st2;



}
#endif
//#include<vector>
//std::vector<int>vec;

#if 1

void print(){
    cout<<"出口一"<<endl;
}
template<class T>
void print(T x){
    cout<<x<<" 出口二 \n";
    //cout<<endl;
}

template<class T , class ...Args>
void print(T x ,  Args ...agrs){
    cout << x << " ";
    sizeof...(Args);
    sizeof...(args);
    print(agrs...); // 解包  , print() 要在上面
}

// double add(){
//     return 0;
// }
// template<class T ,class ...Args>
// double add(T x, Args... args){  //返回值保证精度 
//     return x + add(args...);
// }
 
//同时还可以多个一块解析 , 但必须提供两个出口
double add(){
    return 0;
}
template<class T >
double add(T x ){
    return x;
}
template<class T1,class T2,class ...Args>
double add(T1 x1,T2 x2 ,Args... args){  //返回值保证精度 
    return x1 +x2 +  add(args...);
}
void test(){
    //print(1,2,3,"nihao", 2.3);
    cout<<add( 1.2 , 1 , 2.2 , 3,2)<<endl;;
}
#endif
#if 0
void printType(){
    cout<<endl;
}
template<class T , class ...Args>
void printType(T x ,  Args ...agrs){
    cout << typeid(x).name() << " ";
    printType(agrs...); // 解包  , print() 要在上面
}




void test(){
    printType(1,2,3,"nihao", 2.3);
}
#endif
int main(){
    test();
}