/*
 * @Author: rzk ruanzk2098@gmial.com
 * @Date: 2024-12-14 16:37:30
 * @LastEditors: rzk ruanzk2098@gmial.com
 * @LastEditTime: 2025-01-21 17:12:59
 * @FilePath: /cplusplus/src/inheritance.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include<iostream>

using std::cout;
using std::endl;

namespace PointTest{
class Point{
public:
    Point(int  x,int y):_ix(x) ,_iy(y){
        cout<<"Point()"<<endl;
    }
    void print(){
        cout<<" ( "<<_ix<<","<<_iy<<" ) ";
    }
    ~Point(){cout<<"~Point()"<<endl;}
public :
    int _ix;
    int _iy;
};

class Point3D: public Point{
public:
    //Point3D(int x, int y , int z):_ix(x), _iy(y),_iz(z){}
    Point3D(int x, int y , int z):Point(x,y),_iz(z){ 
        cout<<"Point3D ()"<<endl;
    }
    ~Point3D(){cout<<"~Point3D()"<<endl;}
    void display(){
        print();
        cout<<_ix<<endl;
        cout<<" + "<<_iz <<endl;
    }
private:
    int _iz;
};

void test(){
    Point3D d1(1,2,3);
    d1.display();
    //d1._ix;
}
}

namespace BaseTest{
class Test{
public:Test(int x ): _test(x){}
private: 
    long _test;
};

class Base{
public:
    Base(long x ):_base(x) {
        cout<<"Base()"<<endl;
    }
    void print(){
        cout<<"Base:: print()"<<endl;
    }
    long _data =100; 
private:
    long _base; 
};

class Derived: public Base{
public:
    Derived(long x ,long y):Base(y),_derived(x),_test(x){
        cout<<"Derived()"<<endl;
    }
    long _data = 10;
    // void print(int x ){
    //     cout<<"Derived:: print()"<<endl;
    // }
private: 
    long _derived; 
    Test _test;
};
void test(){
    Derived d(1,2);
    cout<<d._data<<endl;
    cout<<d.Base::_data<<endl;
    d.print();
    //d.print(2);
}
}

namespace mutiInheritanceTest{
class A{
public:
    A(){}
    A(int x):_a(x){}
    void print(){
        cout<<"A:: print()"<<endl;
    }
    int _a;
};

class B : virtual public A{
public:
    B():A(8){}
    int _b = 0;
};
class C: virtual public A{
public:
    C():A(5){}
    int _c = 0;
};

class D : public B ,public C{
public:
 int _d = 0;
};


void test1(){
    D d;
    cout<<d.C::_a<<endl;; 
    cout<<d.B::_a<<endl;; 
    //d.print();
    //d.B::_a;
    //d.C::print();
    // 
}

}
#include<cstring>
namespace test{

class Base{
public:
    // Base(){
    //     cout<<"Base ()"<<endl;
    // }
    Base(long x, const char * pstring):_base(x), _pbase(new char[strlen(pstring)+1]()){
        strcpy(_pbase , pstring);
        cout<<"Base (long x)"<<endl;
    }
    Base(const Base & rhs ):_base(rhs._base) ,_pbase(new char[strlen(rhs._pbase)+1]()){
        strcpy(_pbase , rhs._pbase);
        cout<<"const Base & rhs"<<endl;
    }

    Base&operator=(const Base & rhs){
        if(this != &rhs){
            if(_pbase){
                delete[] _pbase;
                _pbase = new char[strlen(rhs._pbase)+1]();
                strcpy(_pbase , rhs._pbase);
            }
            _base= rhs._base;
        }
        cout<<"Base operator =  "<<endl;;
        
        return *this;
    }
    ~Base(){
        if(_pbase){
            delete[] _pbase;
            _pbase = nullptr;
        }
    }
    void print()const{
        cout<<"_base+ _pbase  "<<_base<<" "<<_pbase;
    }
private:
    long  _base; 
    char * _pbase;
};

class Derived: public Base{
public:
    Derived(const char * pstring,long x , long y):Base(x,pstring), _derived(y){
        cout<<"Derived(long x , long y) "<<endl;
    }
    // Derived(const Derived & rhs):
    //         Base(rhs),    //Base 的拷贝构造 ， 没有的话就默认
    //         _derived(rhs._derived){
    //     cout<<"Derived(const Derived & rhs) "<<endl;
    // }

    // Derived&operator=(const Derived & rhs){
    //     cout<<"Derived operator =  "<<endl;
    //     _derived= rhs._derived;
    //     Base::operator=(rhs);
    //     return *this;
    // }
    void print()const{
        Base::print();
        cout<<"    _derived "<<_derived<<endl;
    }
private:
   int _derived;
};

void test(){
    //Base base(10);
    //Derived d(4,6);
    //base.opreerator=(d);
    //base = d;
    //base.print();
}
void test1(){
    Derived d1("hello",4,6);
    Derived d2("world",5,7);
    d1.print();

    d1 = d2;

    d1.print();

    Derived d3 = d1;  
    d3.print();
}
}
namespace PloymorphismTest
{  

#if 0
class Base{
public:
    Base(long x):_base(x){}
    
    virtual 
    void display() const {
        cout<<"Base display()"<<endl;
    }
    virtual 
    void show() const {
        cout<<"Base show()"<<endl;
    }
    virtual 
    void show1() const {
        cout<<"Base show()"<<endl;
    }
private:
    long _base;
    int a;
};


class Derived :public Base{
public:
    Derived(long base , long derived):Base(base),_derived(derived){}

    void display()const{
        cout<<"Derived display()"<<endl;

    }
 private: 
    long _derived;
};


void test(){
    Derived d1(4,8);
    Base * pb = &d1;
    //在数据成员公有化的情况下， 
    //父类指针指向子类 ， 只能访问父类子对象中的部分
    //pb->_base;
    //pb->_derived;//error , 父类只能访问自己的一亩三分地
    pb->display();  // Base 的

    cout<<sizeof(Base)<<endl;

    cout<<sizeof(Derived)<<endl;
    

    
}
#endif
#if 0
class Grandpa
{
public:
    Grandpa(){ cout << "Grandpa()" << endl; }
    ~Grandpa(){ cout << "~Grandpa()" << endl; }

    virtual void func1() {
        cout << "Grandpa::func1()" << endl;
    }

    virtual void func2(){
        cout << "Grandpa::func2()" << endl;
    }
};

class Parent
: public Grandpa
{
public:
    Parent(){
        cout << "Parent()" << endl;
        func1();//构造函数中调用虚函数
    }

    ~Parent(){
        cout << "~Parent()" << endl;
        func2();//析构函数中调用虚函 数
    }
    virtual void func1() override {
        cout << "Parent::func1()" << endl;
    }

    virtual void func2() override{
        cout << "Parent::func2()" << endl;
    }
};

class Son
: public Parent
{
public:
    Son() { cout << "Son()" << endl; }
    ~Son() { cout << "~Son()" << endl; }

    virtual void func1() override {
        cout << "Son::func1()" << endl;
    }

    virtual void func2() override{
        cout << "Son::func2()" << endl;
    }

};

void test1(){
    Son ss;
    //Grandpa * p = &ss;
    // p->func1();
    // p->func2();

    // cout << sizeof(Grandpa)<<endl;
    // cout << sizeof(Parent)<<endl;
    // cout << sizeof(Son)<<endl;
}

#endif 
#if 1 

class Base{
public:
    Base(long x)
    : _base(x)
    {}

    virtual void display() const{
        cout << "Base::display()" << endl;
    }

    void func1(){  //普通成员函数中调用虚函数
        this->display();   // this 调用
        cout << _base << endl;
    }

    void func2(){
        Base::display();
    }
private:
    long _base = 10;
};


class Derived
: public Base
{
public:
    Derived(long base,long derived)
    : Base(base)
    , _derived(derived)
    {}

    // void func1(){  //普通成员函数中调用虚函数
    //     display();
    //     //cout << _base << endl;
    // }
    
    void display() const override{
        cout << "Derived::display()" << endl;
    }
private:
    long _derived;
};

void test2(){
    Base base(10);
    Derived derived(1,2);

    base.func1();
    base.func2();

    derived.func1(); // Derived的display 
    //通过基类子对象去调用fun1 , this 从 Derived * => Base * 发生转型

    derived.func2();
}
#endif
} // namespace PloymorphismTest
    

namespace CopyControlTest
{
class Base{
public:
    Base(long x):_base(x){}
    void print()const {
        cout<<_base;
    }
private:
    long _base = 10;
};


class Derived : public Base{
public:
    Derived(long x, long y ):Base(x),_derived(y){}
    // Derived(const Derived&c):Base(c),_derived(c._derived){
    //     cout<<"Derived(const Derived&c) "<<endl;
    // }

    // Derived& operator=(const Derived & rhs){
    //     Base::operator=(rhs);
    //     _derived = rhs._derived;
    // }
    void print()const {
        Base::print();
        cout <<"  " << _derived<<endl;
    }
private:
    long _derived = 12;
};

void test(){
    Derived d1(2,3);

    Derived d2(4,5);

    d2.print();
    d2 = d1;

    d2.print();

}


} // namespace test

namespace voerrideTest{
class Base{
public:
    virtual void display()const {
        cout<<"Base::display()"<<endl;
    }
private:
    long _base;
};

class Derived: public Base{
public:

    void display() const override{
        cout<<"Derived::display()"<<endl;
    }

private:
    long _derived;
};
}

#include<string>
using std::string;

namespace purVirtualTest{
#if 0
class A{
public:
    virtual void print() = 0;
    virtual void display() = 0;
} ;

class B : public A{
public:
    virtual void print() override{
        cout<<"B::print()"<<endl;;
    }
    virtual void display() override{
        cout<<"B::display()"<<endl;;
    }

};

void test(){
    //A a;
    B b1;
    A* pa1 = &b1; 

    pa1->print();

    A* pa2 = new B();
    pa2->print();

    A & ref = b1;  // 引用

    ref.display();
}
#endif

#if 0
class A{
public:
    virtual void print() = 0;
    virtual void display() = 0;
} ;

class B : public A{
public:
    virtual void print() override{
        cout<<"B::print()"<<endl;;
    }
};

class C:public B{
public:
    virtual void print() override{
        cout<<"C::print()"<<endl;;
    }

virtual void display() override{
        cout<<"C::display()"<<endl;;
    }
};

void test(){
    //A a;
    //B b1;   //B没有完成所有纯虚函数的实现
    C c1;
    A* pa1 = &c1; 

    pa1->print();

    A* pa2 = new C();
    pa2->print();
     pa2->display();

    // A & ref = c1;  // 引用

    // ref.display();
}
#endif

#if 0 

class Figure{
public:
    virtual string getName() const = 0;
    virtual double getArea() const =0;
};

void display(Figure & fig){
    cout<<fig.getName()<<" 面积 : "<<fig.getArea()<<endl;
}

class Rectangle : public Figure{
public:
    Rectangle(double len , double wid):_length(len), _width(wid){}

    string getName() const override{
        return "矩形";
    }
    double getArea()const override{
        return _length *_width;
    }
private:
    double _length;
    double _width;
};

class Circle : public Figure{
public:
    Circle(double r):_radius(r){}

    string getName() const override{
        return "园";
    }
    double getArea()const override{
        return _radius*_radius*PI;
    }
public:
    double _radius;

    const static double  PI ;
};

//在运行时才能确定的 double型数据，
const double Circle::PI = 3.1415926;


void test(){
    Rectangle r(10, 20);
    Circle c(2);
    display(r);
    display(c);
}
#endif 

#if 0
class Base{
protected:
    Base(int b):_base(b){
        cout<<"Base()"<<endl;
    }
    int _base;
public:
    virtual void print() const {}
    //friend class Derived;
};

class Derived:public Base{
public:
    Derived(int b, int d ):Base(b), _derived(d)
    //,_b1(b)
      {
        cout<<"Derived()"<<endl;
    }

    void print() const override{
        cout<<_base <<"   "<< _derived<<endl;
    }
private:
    int _derived;
    //Base _b1;
};

void test(){

    Derived d1(2,4);
    Base * p = &d1;

    p->print();
}

#endif

#if 0
class Base{
public:
    Base(int b):_pbase(new int(b)){
        cout<<"Base()"<<endl;
    }
    
    virtual void print() const {
        cout<<"Base::print() "<<*_pbase<<endl;
    }
    virtual ~Base(){
        if(_pbase){
            delete _pbase;
            _pbase = nullptr;
        }
        cout<<"~Base()"<<endl;
    }
private:
    int *  _pbase;
};

class Derived:public Base{
public:
    Derived(int b, int d ):Base(b), _pderived(new int(d))
    {
        cout<<"Derived()"<<endl;
    }

    void print() const override{
        cout<<"Derived::print()  "<< *_pderived<<endl;
    }
    ~Derived(){
        if(_pderived){
            delete _pderived;
            _pderived = nullptr;
        }
        cout<<"~Derived()"<<endl;
    }
private:
    int *_pderived;
    //Base _b1;
};

void test(){

    cout<<sizeof(Base)<<endl;    //16
    cout<<sizeof(Derived)<<endl; //24
    Base *pb  = new Derived(2,4);
    pb->print();
    
    delete pb;
   
}
#endif

#if 1 

class Base {
public:
    //Base(long x) :_base(x) {}
    virtual void display() const {
        cout << "Base:display()" << endl;
    }
    virtual void show() const {
        cout << "Base:show()" << endl;
    }
    virtual void print() const {
        cout << "Base:show()" << endl;
    }
    
private:
    long _base  =10;
};


class Derived :public Base {
public:
    //Derived(long base1,long base2 , long derived) :Base1(base1), Base2(base2),_derived(derived) {}

    // virtual void display()const override{   //如果没有覆盖 ， 下面调用会调Base 的
    //     cout << "Derived: display()" << endl;

    // }
    virtual void print() const override{
        cout << "Derived: display()" << endl;
    }

    virtual void show() const override{
        cout << "Derived:show()" << endl;
    }

    virtual void Func() const {   //并没有多出虚表 , 直接在虚表中追加
        cout << "Derived:Func()" << endl;
    }
private:
    long _derived = 100;
};
int a = 0;
const int b = 0;
void  test() {

    Derived d;
    //d.display();
    //将Derived 当作三个存了三个long的结构体
    long* pDerived = reinterpret_cast<long*>(&d);
    //long* pDerived2 = (long*)(&d);
    cout << pDerived[0] << endl;
    cout << pDerived[1] << endl;
    cout << pDerived[2] << endl;
    //cout << pDerived[3] << endl;

    cout<<endl;

    
    
    long * ptable = reinterpret_cast<long*>(pDerived[0]); //

    
    static int num = 0;
    const char * pstr = "hello";
  
    cout<<&num<<"   静态"<<endl; //静态，  全局静态区
    cout<<&a<<"   全局"<<endl;   //全局

    cout<<ptable<<"   ptable"<<endl;    // => 文字常量区

    cout<<&b<<"   全局常量"<<endl;  //全局常量
    printf("%p  字符串常量\n", pstr); //字符串常量
    printf("%p  程序代码区\n  ", test); //程序代码区
    
    cout<<endl;
    cout<<ptable[0]<<endl;
    cout<<ptable[1]<<endl;
    cout<<ptable[2]<<endl;
    //cout<<ptable[2]<<endl;
    typedef void (*Function)();
    Function f1 = (Function)(ptable[0]);  // 哪怕函数私有化也可以调用 
    f1();//从内存上直接通过C的方式调用， 没有类的限制

    Function f2 = (Function)(ptable[1]);  // 哪怕函数私有化也可以调用 
    f2();

    Function f3= (Function)(ptable[2]);  // 哪怕函数私有化也可以调用 
    f3();

     Function f4= (Function)(ptable[3]);  // 哪怕函数私有化也可以调用 
    f4();
    // cout << sizeof(Base) << endl;
    // cout << sizeof(Derived) << endl; 
    // cout << sizeof(int *) << endl;
    // cout << sizeof(long) << endl;

}




#endif 

}//end of namespace purVirtualtest






int main(){
    purVirtualTest::test();
    
}