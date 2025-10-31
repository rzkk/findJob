
#include "mycomplex.h"
#include "myinline.hpp"
#include<cstring>
#include<iostream>
using namespace std;

/*测试cpp基础阶段的代码：
包括： const 
 */
#if 0 
namespace constTest{

#define Max 100

int  a = 10;
const int &b = a;


int func1(int x ,int y)
{
    return x+y;
}
int *func2(int x ,int y)
{
   int *p = new int(2);
   return p;
}

void test1(){
    cout<< Max - 10<<endl;

    const int max = 100;

    cout<<max -10<<endl;


    int num1 = 10 ,num2 = 11;

    const int * p1= &num1;
    cout<<*p1<<endl;

    //*p1 = 3;

    p1 = &num2;
    cout<<*p1<<endl;


    int *const p2 = &num1;
    cout<<*p2<<endl;
    *p2 = 5;
    //p2 = &num2;
    cout<<*p2<<endl;
    ////////////
    int arr1[5] = {1,2,3,4,5};
    int (*p)[5] = &arr1;
    for(int i = 0;i<5;i++)
    {
        cout<<(*p)[i] <<" ";
    }
    cout<<endl;
    cout<<arr1<<endl;
    cout<<&arr1<<endl;

    int num3 = 3,num4 = 4 , num5 = 5;
    int *p3 = &num3;
    int *p4 = &num4;
    int *p5 = &num5;

    int * arr2[3] = {p3,p4,p5};

    for(int i =0;i< 3;i++)
    {
        cout<<*arr2[i]<<"  ";
    }
    cout<<endl;
    ///////////////////////////////////
    int (*f1)(int,int) = &func1;
    cout<<(*f1)(2,3)<<endl;

    int (*f2)(int,int) = func1;
    cout<<f2(2,3)<<endl;
}
int func(){int a = 0;return a;}
void test2()
{
    int r1 = 1;
    const int &r2 = r1 ;
    const int &r3 = 1 ;
    cout<<r2<<endl;
    r1 = 3;
    cout<<r2<<endl;
    // int &r4 = r3;

    // int &r5 = 1;
    // int &ref1 = func();
    // const int &ref2 = func();
    double r6 = 1.0;
    const int &r7 = r6;
    //int &r8 = r6;
    //int &r9 = 1 ;

    cout<<&r6<<endl;
    cout<<&r7<<endl;

}
}//end of constTest
namespace newTest{

void test1()
{   
    int * p1 = new int;
    int *p2 = new int(2);
    cout<<*p1<<" "<<*p2<<endl; 
    
    delete p1 ;
    delete p2;

    int *p3 = new int[10]();
    for(int i = 0;i<10;++i)
    {
        cout<<p3[i]<<" ";
    }
    cout<<endl;
    int *p4 = new int[10];
    for(int i = 0;i<10;++i)
    {
        cout<<p4[i]<<" ";
    }
    cout<<endl;
    int *p5 = new int[10]{1,2,3,4,5,6};
    for(int i = 0;i<10;++i)
    {
        cout<<p5[i]<<" ";
    }


    delete p3;
    delete p4;delete p5;
}
}//end of newTest

namespace memTest{

int g_a= 10;
int g_b= 10;

const int c_g_a = 10;
const int c_g_b = 10;

static int s_g_a = 2;
static int s_g_b= 2;

void test1()
{
    int l_a = 1;
    int l_b = 1;
    static int s_l_a = 2;
    static int s_l_b= 2;

    const int c_l_a = 10;
    const int c_l_b = 10;

    int*pint1 = new int(2);
    int*pint2 = new int(2);

    const char * pstr = "hello";



    cout<<"局部变量a     "<<&l_a<<endl;
    cout<<"局部变量b     "<<&l_b<<endl;

    cout<<"局部常量a     "<<&c_l_a<<endl;
    cout<<"局部常量b     "<<&c_l_b<<endl;

    cout<<"堆上内容1      "<<pint1<<endl;
    cout<<"堆上内容2      "<<pint2<<endl;

    cout<<"全局变量a     "<<&g_a<<endl;
    cout<<"全局变量b     "<<&g_a<<endl;

    cout<<"静态全局变量a "<<&s_g_a<<endl;
    cout<<"静态全局变量b "<<&s_g_b<<endl;
    cout<<"静态局部变量a "<<&s_l_a<<endl;
    cout<<"静态局部变量b "<<&s_l_b<<endl;



    cout<<"全局常量a     "<<&c_g_a<<endl;
    cout<<"全局常量b     "<<&c_g_b<<endl;

    cout<<"字符串常量    "<<(void*)pstr<<endl;

    cout<<"代码区函数    "<<(void*)test1<<endl;
}
}

namespace refernceTest{

int &func()
{
    static int a = 0;
    return a;
}


void test()
{
    func() = 100;
    cout<<func();
}
} //end of refernceTest
namespace castTest{
void test()
{
    //目标类型 转换后的变量 = static_cast<目标类型>(要转换的变量)
    int *p1 = (int * )malloc(sizeof(int));
    *p1 = 100;
    int *p2 = static_cast<int*>(malloc(sizeof(int)));
    *p2 = 100;
    free (p1);
    free (p2);

    float inum = 3.3;
    int fnum = static_cast<int>(inum);

    cout<<inum<<" "<<fnum<<endl;

    const char * p3 = "hello";
    int *pint1 = (int *)p3;
    //*pint1 = 2;    //编译器识别不出来
    char *pchar= (char *)p3;
    //pchar[0] = 'x';    //编译器识别不出来 ,要去改只读内容
    cout<<p3<<endl;
    //不合理的转换会被拒绝
    //int *pint2 = static_cast<int*>(p3);
    //////////////////////
    const int num1 =  100;
    // error: invalid use of const_cast with type ‘int’, which is not a pointer, reference, nor a pointer-to-data-member type
    //const_cast<int>(num1);  //只有引用和指针可以用

    int num2 =10;
    const int & ref1 = num2;
    //int & ref2 = ref1; // error: binding reference of type ‘int&’ to ‘const int’ discards qualifiers 弃限定符
    int & ref2 = const_cast<int&>(ref1); //
    ref2 = 90;
    cout<<num2 << " "<< ref1<<" "<<ref2<<endl; //90 90 90

    const int num3 = 10;
    const int & ref3 = num3;
    int & ref4 = const_cast<int&>(ref3); 
    int & ref5 = const_cast<int&>(num3); 
    ref5 = 100;
    cout<<num3 << " "<< ref3<<" "<<ref4<<" "<<ref5<<endl;    //10 100 100 100  没有改掉
    cout<<&num3 << " "<< &ref3<<" "<<&ref4<<" "<< &ref5<<endl; //0x7ffdcfe8c4e4 0x7ffdcfe8c4e4 0x7ffdcfe8c4e4 0x7ffdcfe8c4e4

    
    const  int * p4 = &num3;
    int *p5 = const_cast<int*>(p4);
    *p5 = 1;
    cout<<num3 << " "<< ref3<<" "<<ref4<<" "<<ref5<<endl;


}
}

#endif
#if 0 
int add(int x ,int y , int z )
{
    return x+y +z;
}

namespace overloadingTest{

int add(int x ,int y)
{
    return x+y;
}
// int add(int x ,int y,int z)
// {
//     return x+y+z;
// }
// float add(float x ,int y)
// {
//     return x+y;
// }
// float add(int x ,float y)
// {
//     return x+y;
// }
// int add( const int x, const int y)
// {
//     return x+y;
// }
// extern "C"
// {
// int add(int x ,int y)
// {
//     return x+y;
// }
//C编译器不允许重名存在
// int add(int x ,int y,int z)
// {
//     return x+y+z;
// }
// float add(float x ,int y)
// {
//     return x+y;
// }
// float add(int x ,float y)
// {
//     return x+y;
// } 
//}
void test()
{
    int a = 1 , b =2, c = 3;
    float d = 2.2;

    cout<<add(a,b,c)<<endl;
    //cout<<add(a,b,c)<<endl;
    //cout<<add(d,a)<<endl;
    //cout<<add(a,d)<<endl;
}
// void fun(int a ,int )
// {}

// void fun(int a ,int = 10)
// {}

}
#endif
#if 0
namespace boolTest{
void test(){
    int a = true;
    int b = false;
    cout<<a<<" "<<b<<endl;

    bool b1 = 1;
    bool b2 = 100;
    bool b3 = -1;
    bool b4 = 0;

    cout<<b1<<" "<<b2<<" "<<b3<<" "<<b4<<endl;

    if(b4){
        cout<<"hello"<<endl;
    }
    cout<<"sizeof(bool)"<<sizeof(b1)<<endl;
}
}


namespace inlineTest{

#define MAX(x,y) ((x) >(y) ?(x) :(y))
#define MULTIPLY(x,y) ((x)*(y))

inline int max(int x ,int y)
{
    return x>y?x:y;
}
inline void print1();
inline void print1()
{
    cout<<"print function1 "<<endl;
}
void print2();
inline void print2()
{
    cout<<"print function2"<<endl;
}



void test()
{
    int i = 4,j =3;
    cout<< MAX(i++,j)<<endl;
    i = 4;
    cout<< max(i++,j)<<endl;

    cout<<multiply(2,3)<<endl;
}

}

namespace cathcTest{

double division(double x,double y)
{
    if(y == 0){
        throw "Deivision by zero";
    }
    return x/y;
}

void test(){
    double x = 100, y = 0;

    try{
        cout << division(x,y) << endl;
    }catch(const char * msg){ //catch的小括号里是类型
        //cout << "hello" << endl;
        cout << "hello," << msg << endl;
    }catch(double x){
        cout << "double" << endl;
    }catch(int x){
        cout << "int" << endl;
    }
}
}

namespace c_str_test{
void test()
{
    char arr1[6] = {'h' ,'e' , 'l' , 'l','o' }; //后面会补一个 '\0'
    cout<<arr1<<endl;
    cout<<arr1+1<<endl;

    char arr2[] = {'h' ,'e' , 'l' , 'l','o' };  //不会补  '\0'
    cout<<arr2<<endl;

    char arr3[] = "hello";    //后面会补一个 '\0'   ， "" 在常量区 ，创建数组的时候复制一份到栈
    cout<<arr3<<endl; 

    char * p1 = "world"; //warning: ISO C++ forbids converting a string constant to ‘char*’  不可被修改的内容
    const char * p2 = "world"; //推荐
    cout<<p1<<endl;
    cout<<p2<<endl;
     
    int a =0, b =0,c = 0;    //
    int arr4[] ={a,b,c};     // 会复制一份a，b，c放到数组里面
    cout<<&a<<"\n";
    cout<<arr4<<endl;

    //"hello" ,单独的“ ” 是被认为是const char * 
    cout<<"hello"+1 <<endl;   // 指针偏移 ， ello

    char *p3 = new char[strlen(p2)+1](); //这里的空间是允许修改的
    strcpy(p3,p2);
    cout<<p3<<endl;
    delete[] p3;
    p3 = nullptr;
}
}

#endif

#include"baseCpp.hpp"
// Computer g("g" ,2000);
// static Computer s_g("s_g" ,2000);
// const  Computer c_g("c_g" ,2000);
// static const  Computer s_c_g("s_c_g" ,2000);  //同一区域按照先后顺序
namespace ClassTest{



void test1()
{

    // int num ;

    //Computer c1("l", 1000000);
    //Computer c2;
    //c2 = c1;
    //c2 = c2;
    // static Computer s_l("s_l" , 1000000);

    // const Computer c_l("c_l", 1000000);
    // c2.showinfo();

    // c2.~Computer();
    // c2.showinfo();
    
    Point p1(1,2);   
    //Point p2(1,2);   
   // Point p3(1,2);   
   

    //Point p6{1,2,&a}; 
   
    //Point p2 = p1 , p3 ;
    //, p3;
    //p2 = p3 = p1;
    // //p1.setX(4);
    // //p1.setY(5);
    // p1.print();

    // Point p2(1,7);
    //p1 =p1;


    //p2.operator=(p1);    
    
    //p2.print();
    //p3.print();

    //cout<<sizeof(Point)<<endl;
    // int a1(10);
    // int a2();   //这是个函数声明
    // a2 = 2;
    // cout<<a1<<" "<<a2<<endl;;

    // const char* pstr = "hello";
    // cout<<strlen(pstr)<<endl; 

    // Computer*p = new Computer("dui" , 1000);
    // delete p;

    Point p4 = Point(p1);
    Point p5 = {2,3}; 

    Line l1;
    l1.print();
    cout<<"\n\n";

    Line l2(6,7,8,9);
    l2.print();
    cout<<"\n\n";

    Line l3(p4,p5);
    l3.print();
    cout<<"\n\n";
}

void test2()
{
   
    // Point p;
    // p.print();
    // Point p1(1,7);

    // Point p2 = p1;
    // p2.print();

    // Point p3(p1);

    Computer c1("xiaomi" ,20000);
    Computer c2 ("huawei",21000);
    Computer c3 ("Acer",8000);

    c1.showinfo();
    c2.showinfo();
    c3.showinfo();

    Computer c4  = c1;
    c4.showinfo();

    c2 = c1;
    c1.showinfo();
    c2.showinfo();
    c3.showinfo();
}

class SinglePoint {
public:

    static SinglePoint * getInstance(){
        if(_pInstance == nullptr){
            _pInstance = new SinglePoint();
        }
        return _pInstance;
    }
    static void destory(){
        if(_pInstance != nullptr){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
    void print() const {
        if(_str)
            cout<<"( "<<_ix<<"  "<<_iy<<" )   "  <<_str<<endl;
        else 
            cout<<"( "<<_ix<<"  "<<_iy<<" )   "  <<"空 "<<endl;
    }
    void setXY(int x,int y , const char *str){
        if(_str){
            delete _str;
            _str = nullptr;
        }
        _str = new char[strlen(str)+1]();
        strcpy(_str, str);
        _ix = x;
        _iy = y;
    }

private:
    SinglePoint():_ix(0),_iy(0),_str(nullptr){
        cout<<"创建\n";
    }
    SinglePoint(int x ,int y ,const char *str):_ix(x),_iy(y),_str(new char[strlen(str)+1]()){
        strcpy(_str,str);
    }

    ~SinglePoint(){
		if(_str)
        {
            delete[] _str;
            _str = nullptr;
        }
	}
    SinglePoint(const SinglePoint &p) = delete;
    SinglePoint&operator=(const SinglePoint&sp) = delete;
    
    int _ix;
    int _iy;
    char *_str;
    static SinglePoint * _pInstance;
};
SinglePoint * SinglePoint::_pInstance = nullptr;

void test3()
{
    //SinglePoint p1 = SinglePoint::getInstance(); // 私有的拷贝构造
    //SinglePoint p2 = SinglePoint::getInstance();
    // SinglePoint * p1 = SinglePoint::getInstance(); 
    // SinglePoint * p2 = SinglePoint::getInstance();
   
    // p1->print();   
    // p2->print();
    //delete p1;

    SinglePoint::getInstance()->print();
    SinglePoint::getInstance()->setXY(3,5 , "nihao ");
    SinglePoint::getInstance()->print();
    //SinglePoint::getInstance()->destory();
    SinglePoint::destory();
    //SinglePoint::getInstance()->destory();
    SinglePoint::getInstance()->print();


}
}
class Stack{
    
};
int main()
{
    ClassTest::test3();
    
    //overloadingTest::test();
    // Point2 myp1(1,1), myp2(4,5);

	// Distance myd(myp1, myp2);
	// cout << "The distance is:" ;
	// cout << myd.GetDis() << endl;

    //int a = 0;
    //int *const p =  &a;
    //int * b = p;

    //const int * p2 = &a;
    //int * b1 = p2;
    // Point pts1[2] = {{1, 2}, {3, 4}};
    // Point p1 ,p2;
    // Point pts2[2] = {p1, p2};

    // Point p1(2,3);
    // Point p2(3,4);

    // Point *pt1 = new Point(11,21);
    // delete pt1; 
    // pt1 = nullptr;

    // Point *pt2 = new Point[2]{{1,2},{3,4}};
    // Point *pt3 = new Point[2]{p1,p2};


     //Point *pt2 = new Point[2]({2,3},(2,3));

    // func(p1,p2);
    //func(&a);
    //func(&b);
    //cout<<num<<endl;
    // char* p1 = new char[2]();

    // if(p1)
    // {
    //     cout<<"519\n";
    //     delete [] p1 ;
    //     p1 = nullptr;
    // }
    // if(p1)
    // {
        
    //     cout<<"526\n";
    // }

    //math_Fun::Complex c1(2,3);
    //c1.showComplex();

    //cout<<"/////////////////////////////////////\n";
    // int arr[5] = {1,2,3,4,5};
    // cout<<arr<<endl;
    // cout<<&arr<<endl;
    // cout<<arr+1<<endl;
    // cout<<&arr+1<<endl;

    // int *p = (int *)(&arr+1);

    // cout<<*(arr+1)<<endl;
    // cout<<*(p-1)<<endl;

    // int * p1 = new int[5]{1,2,3,4,5};
    // cout<<p1[2]<<endl;;

    // const char * p2 = "sdds\0dsd";
    // char * p3 = new char[10]();
    // strcpy(p3,p2);
    // cout<<strlen(p2)<<endl;
    // cout<<p3<<endl;
    return 0;
}