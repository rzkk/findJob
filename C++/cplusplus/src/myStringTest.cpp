/*
 * @Author: rzk ruanzk2098@gmial.com
 * @Date: 2024-12-08 19:33:30
 * @LastEditors: rzk ruanzk2098@gmial.com
 * @LastEditTime: 2024-12-09 18:05:35
 * @FilePath: /cplusplus/src/myStringTest.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "myString.h"

using std::cout;
using std::endl;
using std::size_t;

void test1(){
    String s1;
    String s2("Hello word!");
    String s3(s2);
    std::cout<<s2.c_str()<<std::endl;
    std::cout<<s3.c_str()<<std::endl;
   
    String s4 = s2;
    String s5 = "nihao !";
    s4 = s3;
    s5 = "qwert";

    std::cout<<s4.c_str()<<endl;
    std::cout<<s5.c_str()<<endl;

    s5 += s4;

    cout<<s5.c_str()<<endl;

    s5+= " dsds";
    cout<<s5.c_str()<<endl;
}
void test2(){
    String s1("Hello");
    //  cout<<s1.size()<<endl;
    //  for(size_t i = 0;i< s1.size();++i ){
    //     cout<<s1[i]<<" ";
    //  }
    //  cout<<endl<<s1<<endl;

    //  cout<<endl;
    //  const String s2("hhhh");
    //  cout<<s2[2]<<endl;;
     std::cin>>s1;
     cout<<s1<<endl;;
     cout<<s1.size()<<endl;
}
//优化右值对象创建对象
//拷贝构造有两种 左值 右值都有可能
void test3(){
    //String s1("hello");
    //String s2 = s1;

    String s3 = "hello";
    String s4 = s3;

    s4 = String("word");


}
//左右值
void test4(){
    int a = 10, b = 10 ;
    //&(a+b); // 右值
    //&1;
    //cout<<&"hello"<<endl;
    //String *ps = new String("hello");  //这里的“hello“ 存在堆上
    //cout <<sizeof(String);

    int & ref1 = a; //左值引用
    const int & cref2 = b; //const 左值引用
    //非const 左值引用只能绑定左值 , const 左值引用可以绑定左值 + 右值
    const int & ref3 = a+b;//虽然是右值，但是也是存在内存中的
    const int & ref4 = 1;  //创建临时变量
    //cout<<&ref4<<endl;
     
    //String("hell");
    const String &s = String("hell"); // 加了const左值引用之后 生命被延长
    cout<<"11111"<<endl;
}
//右值引用
void test5(){
    int a = 1, b =1;
    int && ref1 = a+b;
    //int && ref2 = a;
    &ref1; //可以取地址
}

//std::move()
void test6(){
    int a = 1;
    cout<<&a<<endl;
    cout<<std::move(a)<<endl;
    //std::move(a) = 2;
    int && ref = std::move(a);
    ref = 2;

    cout<<a<<endl;
    cout<<&a<<endl;
    cout<<&ref<<endl;    //所有的地址都相同 ， 内存中就这一份

    ////////////////////////
    cout<<endl;
    String s1("Heloo");
    cout<<s1<<endl;

    String s2 = std::move(s1);  //移动构造
    cout<<s2<<endl;
    s2 = "word";

    cout<<s1<<endl;  
    //s1 没了 ， 
    //因为在移动构造中， 把右值释放掉了 ， 影响到了s1本体 
    cout<<s2<<endl;
}
///////////////
//右值引用本质
int  fun1(){ 
    int num = 10;
    cout<<&num<<endl;;
    //return std::move(num);
    return num;
}
int gnum =1;
int & fun2(){ 
   
    return gnum;
}
int && fun3(){   // 要返回右值引用
    return 1; 
}
int && fun4(){   // 要返回右值引用
    int num = 1; 
    return std::move(num); 
}
void test7(){
   // &fun();
    int &&ref = fun1(); //返回局部对象的副本temp ，右值
    cout<<ref<<endl;
    cout<<&ref<<endl;

    &fun2();  //匿名左值引用， gnum 的引用 ， 取址就是gnum 


    //&fun3(); //error : 1 不在内存上  , 右值属性的右值引用

    // &fun4();  //右值属性的右值引用 ，不能取地址
    //int &&ref2 = fun4(); //左值属性的右值引用
    //cout<<ref2<<endl; // error 绑定值已经被销毁
    //左值引用还是左值 ： 不管有没有名字
    //有名字的右值引用时左值， 无名字的时右值
    //cout<<"1111"<<endl;
}

////////
//测试返回值的临时变量 是移动构造还是拷贝构造
String fun(){
    String s1("hello");
    return s1;
}
void test8(){
    fun();  //返回的临时变量是移动构造 
    //return 的是要销毁的对象时， 移动构造 , 否则拷贝构造
}
int main(){
    test8();
}