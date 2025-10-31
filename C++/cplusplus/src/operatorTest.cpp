#include<iostream>
#include<cmath>
using std::cout;
using std::endl;

namespace friendTest{

class Point;

class Line{
public:
    float distance(const Point&p1 , const Point & p2);
};

class Point{
public:
    Point(int x ,int y):_ix(x),_iy(y){}
    //friend class Line;
    friend float Line::distance(const Point&p1 , const Point & p2);
    friend float distance(const Point&p1 , const Point & p2);
    friend class PointTest;
private:
    int _ix ;
    int _iy;
};

class PointTest{
public:
    void print(const Point &p){
        cout<<p._ix<<" "<<p._iy<<endl;
    }
};

float Line::distance(const Point&p1 , const Point & p2){
          return sqrt((p1._ix - p2._ix) * (p1._ix - p2._ix) + 
                (p1._iy - p2._iy) * (p1._iy - p2._iy) );
}

float distance(const Point&p1 , const Point & p2){
    return sqrt((p1._ix - p2._ix) * (p1._ix - p2._ix) + 
                (p1._iy - p2._iy) * (p1._iy - p2._iy) );
}

void test(){
    Point p1(0,0);
    Point p2(3,4);
    Line l1;
    PointTest pt;
    cout<<l1.distance(p1,p2)<<endl;;
    cout<<distance(p1,p2)<<endl;
    pt.print(p2);
}
}

#include <fstream>
#include<cstring>
#include <limits>
namespace complexTest{

void inputInt(std::istream & is , int & num );

class Complex{
public:
    Complex(int x = 0, int y = 0):_real(x),_image(y){}

    Complex operator+(const Complex & c){
        return Complex(_real + c._real , _image + c._image);
    }
    //friend Complex operator+(const Complex&c1 , const Complex& c2 );
    friend std::ostream& operator<<(std::ostream &os,const Complex&c);
    friend std::istream& operator>>(std::istream &is, Complex&c);

    Complex & operator+=(const Complex & c){
        _real += c._real;
        _image += c._image;
        return *this;
    } 

    Complex & operator++(){
        ++_real;
        ++_image;
        return *this;
    }

    Complex  operator++(int){
        Complex temp(_real, _image);
        ++_real;
        ++_image;
        return temp;
    }
    // int getReal() const {
    //     return _real;
    // }
    // int getImage()const{
    //     return _image;
    // }
    void print(){
        cout<<_real <<" + "<<_image<<" i  "<<endl;
    }
private:
    int _real;
    int _image;
};

// Complex operator+(const Complex&c1 , const Complex& c2 ){
//     return Complex(c1.getReal() + c2.getReal() , c1.getImage() + c2.getImage());
// }
// Complex operator+(const Complex&c1 , const Complex& c2 ){
//     return Complex(c1._real + c2._real , c1._image + c2._image);
// }
std::ostream& operator<<(std::ostream &os , const Complex&c){
    os<<c._real<< " + "<<c._image<<" i ";
    return os;
}
std::istream& operator>>(std::istream &is , Complex&c){
   // is>>c._real >> c._image;
    inputInt(is , c._real);
    inputInt(is , c._image);
    return is;
}

void inputInt(std::istream & is , int & num ){
    using std::cin;
    while(cin >>num , !cin.eof()){
        if(cin.bad()){
            cout<<"cin has broken "<<endl;
            return ;
        }else if(cin.fail()){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cout<<"please input a integer \n";
        }else{
            break;
        }

    }
}
void test1(){
    Complex c1(2,3);
    cout<<c1<<endl;

    std::ofstream ofs("operator2file.txt",std::ios::app);
    ofs<<c1<<endl;
    ofs.close();

    std::cin>>c1;  
    //operator>>(cin , c1);
    cout<<c1<<endl;

}
void test(){
    Complex c1(3,4);
    Complex c2(5,6);

    Complex c3;// = c1 +c2;
    Complex c4;
    Complex c5;
    c3.print();
    //c3 = c1.operator+(c2);
    //c3 = operator+(c1,c2);
    c3 = c1 + c2;
    c3.print();

    c2 += c3;
    c2.print();


    c3.print();
    c3++;

    ++c3;
    c3.print();

    c2.print();
    c2.operator++();
    c2.operator++(1);
    c2.print();

    //cout<<&(c3++)<<endl;
    //Complex & ref = (c3++);
    cout<<"  \n";
    //ref.print();
    int a = 0;
    cout<<&(++a)<<endl;
    //cout<<&(a++)<<endl;
}

}

namespace CharArrayTest{

class CharArray{
public:
    CharArray(const char * pstr):_capacity(strlen(pstr)+1) , _data(new char[_capacity]()){
       strcpy(_data , pstr); 
    }
    ~CharArray(){
        if(_data){
            delete [] _data;
            _data = nullptr;
        }
    }

    char & operator[](size_t index){
        if(index < _capacity-1){  // 包含'\0'
            return _data[index];
        }else{
            cout<<"out of range"<<endl;
            static char nullchar = '\0';
            return nullchar;
        }
    }
    
    // 返回值const 阻止 ，arr[0] = 'd'; //
    // 但是 _data指向的空间无const属性，
    //尾部 const ,给this 加 ，类成员变量无法修改 ， 可以重载
    const char & operator[](size_t index)const{
        if(index < _capacity-1){  // 包含'\0'
            return _data[index];
            //_data[index] = '2'; //这种修改无法避免
        }else{
            cout<<"out of range"<<endl;
            static char nullchar = '\0';
            return nullchar;
        }
    }
private:
    size_t _capacity;
    char *_data;
};

void test3(){
    CharArray arr("hello");
    cout<<arr[0]<<endl;
    char &a = arr[0];
    a = 'd'; //
    const CharArray arr_c("word!");

    cout<<arr[0]<<endl;  //arr中data 指向的空间没有const属性
    char &b = arr[0];
    b = 'd'; //
    //arr_c[3] = 'd'; // const
}
}

namespace DataTest{

class Data{
public :
    Data(){}
    ~Data(){
        //cout<<"~Data\n"<<endl;
    }
    int getData(){ return _data;}
private:
    int _data = 10;
};

class MiddleLayer{
public:
    MiddleLayer(Data *p):_pdata(p){}
    ~MiddleLayer(){
        if(_pdata){
           delete _pdata;
           _pdata = nullptr; 
        } 
        //cout<<"~MiddleLayer\n";
    }
    // int getData(){
    //     return _pdata->getData();
    // }
    Data * operator->(){
        return _pdata;
    }

    Data & operator*(){
        return *_pdata;
    }
private:
    Data * _pdata;
};


class ThirdLayer{
public:
    ThirdLayer(MiddleLayer *p):_pml(p){}
    ~ThirdLayer(){
        if(_pml){
           delete _pml;
           _pml = nullptr; 
        } 
    }

    // Data * operator->(){
    //     //return (*_pml).operator->();
    //     return _pml->operator->();
    // }

    // MiddleLayer * operator->(){
    //     return _pml;
    // }


    // MiddleLayer & operator->(){  //middleLayer 对象调用重载 -> , 
    //     return *_pml;
    // }

    // MiddleLayer & operator*(){
    //     return *_pml;
    // }
    //一步到位
    //  Data & operator*(){
    //     return *(*_pml);
    //  }
    
private:
    MiddleLayer * _pml;
    
};
void test2(){

    ThirdLayer tl(new MiddleLayer(new Data()));
    //cout<<tl->getData()<<endl; //对应 294行
    //cout<< tl.operator->()->operator->()->getData();   //299行 这里面全是指针调用了
    //  tl.operator->()->getData();
    //    cout<<tl->getData()<<endl;;

   //cout<<(*(*tl)).getData()<<endl;;
    // 
//    (*(tl.operator*())).getData();
//     tl.operator*().operator*().getData();
//     (*tl)->getData();
  // cout<<((*tl)).getData()<<endl;

    //一步到位
    //(*tl).getData();

}
void test1(){
    //Data d1;
    //MiddleLayer m1(&d1);

    // Data *p = new Data();
    // MiddleLayer m2(p);
    // delete p;

    MiddleLayer m3(new Data());
    //cout<<m3.getData()<<endl;;
    cout<<m3->getData()<<endl;;
    cout<<(*m3).getData()<<endl;;

    ThirdLayer tl(&m3);  // delete  栈上对象了

}

}

namespace functionTest{
class funcObject{
public:
    void operator()(){
        cout<<"operator()()"<<endl;
    }
    int  operator()(int ){
        cout<<"operator()(int)"<<endl;
        return 5;
    }
};
void display(int x ){
    cout<<"display "<<x<<endl;
}
void print(int x ){
    cout<<"print "<<x<<endl;
}
typedef void (*FunType)(int);
void test1(){
    // funcObject f;
    // f();
    // cout<<f(1)<<endl;;

    //函数指针
    // void (*p)(int) = display;
    // p(4);
    // p(3);

    // p = print;  // 同类型的
    // p(2);


    // void (*p2)(int) = display;
    // (*p2)(2);

    // p2 = &print;
    // (*p2)(3);

    FunType f = print;
    f(2);
    f = display;
    f(2);
}

class FFF{
public:
    void print(int x ){
        cout<<"FFF::print()  "<<x<<endl;
        cout<<y;
    }
    void display(int x ){
        cout<<"FFF::display()  "<<x<<endl;
    }
    static void show (int x){
        cout<<"static FFF::show()  "<<x<<endl;
    }
    int y  =0 ;
};

typedef void (FFF::*FFFFunType)(int);
void test(){
    //静态的不需要通过对象去调用
    FunType f1 = FFF::show;  // 静态成员函数可以直接用省略形式
    f1(3);


    //void (*f2)(int) = FFF::print; //error : 普通函数指针无法指向类的非静态成员函数
    //需要定义一个成员函数指针才能指向类非静态成员函数
    //指针名前加上作用域
    // 只能使用完整形式
    void (FFF::*f2)(int) = &FFF::print;
    FFFFunType f3 = &FFF::print; // 在typedef时加上类作用也可以
    //f2(2); //只能通过对象调用
    //f3(2);

    FFF fff;
    (fff.*f2)(2);
    (fff.*f3)(2);

    FFF* ff1 = new FFF();
    (ff1->*f2)(2);

    FFF * f = nullptr;
    f->print(20);
}
}


namespace nestClass{
class Line{
private:
    class Point{
    public:
        Point (int x ,int y):_ix(x),_iy(y){}
        friend std::ostream & operator<<(std::ostream &os , const Point & p);

        friend class Line; 
        //friend  void Line::getPoint(); 声明友元成员函数不行
        void print(){}
        void getLine(const Line& l ){
            //l._p1 ;
            cout<<l.length ;
            cout<<_p3;  //外部类的静态成员不需要对象和类名访问  ， //? 这也是友元的特点 仅仅是友元类
                        // :: 访问静态成员和内部类 ， 所以Line 的静态数据成员与Point 同一个作用域下 
            cout<<Line::_p3;
        }
    private:
        int _ix;
        int _iy;
        static int _iz;
    };

public:
    Line(int x1,int y1 , int x2 ,int y2 ):_p1(x1,y1),_p2(x2,y2){} //只有初始化可以这样写
    friend std::ostream & operator<<(std::ostream &os , const Line & l);
    friend std::ostream & operator<<(std::ostream &os , const Point & p);

    void getPoint(){
        _p1.print(); //外部类 通过内部类对象访问内部类的公有成员
        //_p1._ix ;    //外部类 通过内部类对象访问内部类的私有成员  ，相当于在Point类外通过对象访问私有成员，需要声明友元类 禁止 ， 
        Point::_iz = 10; // 需要声明友元
    }
private:
    Point _p1;
    Point _p2;
    double length = 10;
    static int _p3;
};
//内部类的静态成员 初始化要放在外部类的外面
int Line::Point::_iz = 10; 
int Line::_p3 = 0;

//void getPoint(){}
//若Point 是Line的私有成员， 则Line::Point 在类外无法使用 ， 因此需要在Line 类中进行友元声明
//让这个函数可以使用这个私有类
//同时函数访问Point的私有成员 因此需要在Point 类中也需要声明友元
std::ostream & operator<<(std::ostream &os , const Line::Point & p){
    os <<"( "<< p._ix<<" , "<<p._iy<<" )";
    return os;
}

std::ostream & operator<<(std::ostream &os , const Line & l){
    os << l._p1<<" --> "<<l._p2;
    return os;
}

void test(){
     //Line::Point pt1(3,4);
    Line l1(1,2,3,4);
    //Point pt2(1,2);
    // cout<<sizeof(Line)<<endl;
    // cout<<sizeof(l1)<<endl;

    // cout<<sizeof(Line::Point)<<endl;
    // cout<<sizeof(pt1)<<endl;

    cout<<l1<<endl;
    
}
}

#include "pimpl.h"
namespace LineImplTest{
void test(){
    Line l(1,2,3,4);
    l.printLine();
    
}
}

namespace autoReleasaTest{
class Singleton {
public:

    static Singleton * getInstance(){
        if(nullptr == _pInstance  )   // 避免手误， 少打一个 = 
        {
            _pInstance = new Singleton();
        }
        return _pInstance;
    }
   
    // static void destory(){
    //     if(nullptr != _pInstance ){  //避免多次调用
    //         delete _pInstance;      // 调析构
    //         _pInstance = nullptr;
    //     }
    // }
    void print() const {
        if(_str)
            cout<<"( "<<_ix<<"  "<<_iy<<" )   "  <<_str<<endl;
        else 
            cout<<"( "<<_ix<<"  "<<_iy<<" )   "  <<endl;
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
    friend class AutoRelease1;
    friend class AutoRelease2;
private:
    Singleton():_ix(0),_iy(0),_str(nullptr){}
    Singleton(int x ,int y ,const char *str):_ix(x),_iy(y),_str(new char[strlen(str)+1]()){
        strcpy(_str,str);
    }
    Singleton(const char *str):_ix(0),_iy(0),_str(new char[strlen(str)+1]()){
        strcpy(_str,str);
    }
    ~Singleton(){    //为了避免多指针指向单例
        if(_str)
        {
            delete[] _str;
            _str = nullptr;
        }
	}
    
    Singleton(const Singleton &p) = delete;
    Singleton&operator=(const Singleton&sp) = delete;
    
    int _ix;
    int _iy;
    char *_str;
    static Singleton * _pInstance;
};
Singleton * Singleton::_pInstance = nullptr;

//PTHREAD_ONCE_INIT
class AutoRelease1{
public:
    AutoRelease1(Singleton*p):_p(p){
        cout<<"AutoRelease1(Singleton*)"<<endl;
    }
    ~AutoRelease1(){
        cout<<"~AutoRelease1()"<<endl;
        if(_p){
            delete _p;
            //_p->destory();
            _p = nullptr;
        }
    }

private:
    Singleton *_p;
};

void test2(){
    AutoRelease1 ar1(Singleton::getInstance());  // 现在是两个指针指向同一块空间，double free
    Singleton::getInstance()->print();
    //AutoRelease1 ar2(Singleton::getInstance("hello"));
    // Singleton::getInstance()->print();   //两次delete 
    //Singleton::destory(); 
}

class AutoRelease2{
public:
    AutoRelease2(Singleton*p){
        if(!_p){
            _p = p;
        }
        cout<<"AutoRelease2(Singleton*)"<<endl;
    }
    ~AutoRelease2(){
        cout<<"~AutoRelease2()"<<endl;
        if(_p){
            delete _p;
            //_p->destory();
            _p = nullptr;
        }
    }


private:
    static Singleton *_p;
};
Singleton*  AutoRelease2::_p = nullptr;
//Singleton*  AutoRelease2::_p = Singleton::getInstance();

void test(){
    AutoRelease2 ar1(Singleton::getInstance());  // 现在是两个指针指向同一块空间，double free
    Singleton::getInstance()->print();
    AutoRelease2 ar2(Singleton::getInstance());
    // Singleton::getInstance()->print();   //两次delete 
    //Singleton::destory(); 
}
}

namespace SingletonImplTest{
class Singleton {
private:
    class AutoRelease{ // 私有内部类 ， 在外部无法创建 
    public:            // 外部类内可访问 ， 外部类外无法访问
        AutoRelease(){}
        ~AutoRelease(){
            //cout<<"~AutoRelease2()"<<endl;
            if(_pInstance){
                delete _pInstance;
                //_p->destory();
                _pInstance = nullptr;
            }
        }
    };

public:
    static Singleton * getInstance(){
        if(nullptr == _pInstance  )   // 避免手误， 少打一个 = 
        {
            _pInstance = new Singleton();
        }
        return _pInstance;
    }
    static Singleton * getInstance(const char* s){
        if(nullptr == _pInstance  )   // 避免手误， 少打一个 = 
        {
            _pInstance = new Singleton(s);
        }
        return _pInstance;
    }
       static void destory(){
        if(nullptr != _pInstance ){  //避免多次调用
            delete _pInstance;      // 调析构
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
    friend class AutoRelease1;friend class AutoRelease2;
private:
    Singleton():_ix(0),_iy(0),_str(nullptr){}
    Singleton(int x ,int y ,const char *str):_ix(x),_iy(y),_str(new char[strlen(str)+1]()){
        strcpy(_str,str);
    }
    Singleton(const char *str):_ix(0),_iy(0),_str(new char[strlen(str)+1]()){
        strcpy(_str,str);
    }
    ~Singleton(){    //为了避免多指针指向单例
        if(_str)
        {
            delete[] _str;
            _str = nullptr;
        }
	}
    
    Singleton(const Singleton &p) = delete;
    Singleton&operator=(const Singleton&sp) = delete;
    
    int _ix;
    int _iy;
    char *_str;
  
    static Singleton * _pInstance; 
    //static AutoRelease ar; 
    //含有AutoRelease 对象 才是嵌套的
    //想通过ar的析构 回收Singleton 
    //如果是定义的普通函数 ，那么变量是在堆上 ， 因此释放需要手动，其析构无法自动调用
    //AutoRelease ar;
    static AutoRelease ar;  //静态的变量是os管理释放的
    
};

Singleton * Singleton::_pInstance = nullptr;
Singleton::AutoRelease Singleton::ar;

void  test(){
    Singleton::getInstance("hello"); 
    Singleton::getInstance()->print();
    Singleton::destory();  
    //没有多个指针指向空间的问题 ， 不管是destory还是ar 的析构，用的都是_pInstance

}

}

namespace atexitTest{
void display(){
    cout<<"display()"<<endl;
}
void  print(){
    cout<<"print()"<<endl;
}
void test(){
    atexit(display);
    atexit(print);
}
}

#include"CowString.h"
namespace CowStringTest{
void test(){

    CowString str1;
    cout<<str1.getRefCount()<<endl;
    CowString str2 = str1;
    cout<<str1<<endl;
    cout<<str2<<endl;

    cout<<str1.getRefCount()<<endl;
    cout<<str2.getRefCount()<<endl;

    CowString str3("hello");
    CowString str4 = "world";
    cout<<str4<<endl;

    str2 = str4;
    str4 = str3;

    cout<<str3<<endl;

    cout<<str4<<endl;
    
    cout<<str1.getRefCount()<<endl;
    cout<<str2.getRefCount()<<endl;
    cout<<str3.getRefCount()<<endl;
    cout<<str4.getRefCount()<<endl;

}

void test1(){
    CowString str1 = "hello";
    CowString str2 = str1;

    cout<<str1<<endl;
    cout<<str2<<endl;
    cout<<str1.getRefCount()<<endl;
    cout<<str2.getRefCount()<<endl;
    str1[2] = 'a';
    cout<<str1.getRefCount()<<endl;
    cout<<str2.getRefCount()<<endl;
    cout<<str1<<endl;
    cout<<str2<<endl;
}
}

class Complex;

class Complex{
public:
    Complex(int x ,int y = 1):_ix(x),_iy(y){}
    void print(){
        cout<<_ix <<"  "<<_iy<<endl;
    }
private:
    int _ix;
    int _iy;
};

class Point{
public:
    Point(int x ,int y = 1):_ix(x),_iy(y){}
    operator int(){
        return _ix + _iy;
    }
    operator Complex(){    
        return Complex(_ix, _iy);   //Complex的完整类型必须在调用之前
    }
private:
    int _ix;
    int _iy;
};
// void test(){
//     Point p1(2,3) ;
//     Complex c1(4,5);
//     c1 = p1;
//     int a = p1;
//     cout<<a<<endl;
//     c1.print();
// }

namespace test{

class Line{
public:
    class Point{
    public:
        Point (int x ,int y):_ix(x),_iy(y){}
    private:
        int _ix;
        int _iy;
    };

public:
    Line(int x1,int y1 , int x2 ,int y2 ):_p1(x1,y1),_p2(x2,y2){} //只有初始化可以这样写

private:
    Point _p1;  // 成员子对象
    Point _p2;
};

void test(){
    cout<< sizeof(Line)<<endl;;
    cout<< sizeof(Line::Point) <<endl;
}
}
void init_r(){

}
#include<pthread.h>
int main(){
    //CowStringTest::test1();
    //functionTest::test();
    //SingletonImplTest::test();
    //pthread_once_t _once = PTHREAD_ONCE_INIT;
    //pthread_once(&_once,init_r);
    //int a = 0;
    //pthread_once(&a,init_r);
    std::string str1 = "helloworld";
    cout<<sizeof(str1)<<endl;
    cout<<str1.size()<<endl;
    cout<<str1.capacity()<<endl;

    std::string str2 = "helloworld!!!!!!!!!!!";
    cout<<sizeof(str2)<<endl;
    cout<<str2.size()<<endl;
    cout<<str2.capacity()<<endl;
    cout<<sizeof(size_t)<<endl;
    return 0;
}