#include<iostream>
using std::cout;
using std::endl;;


#if 0
#include<functional>
#include<cmath>
using std::bind;
using std::bind1st;
int add(int x ,int y){return x+y;}
int multiply(int x ,int y,int z){return x+y+z;}

class Point{
public:
    Point(int x , int y):_ix(x),_iy(y){}
    //template<class T>
    double  add() const{
        return sqrt (pow(_ix,2) + pow(_iy,2));
    }

    Point * Data(){
        return this;
    }

    int _ix = 0;
    int _iy = 0;

};


void test1(){
    auto f1 = bind(add ,1,2);
    auto f2 = bind(multiply ,1,2,3);
    auto f3 = bind(&Point::add , Point(1,2).Data());
    cout<<f1()<<endl;
    cout<<f2()<<endl;
    cout<<f3()<<endl;
}

void func1(int x, int y , int z , const int &u , int & v,int w){
    cout<<"x = "<<x<<endl<<"y= "<<y<<endl<<"z= "<<z<<endl<<"u= "
    <<u<<endl<<"v= "<<v<<endl<<"w = "<<w<<endl;;
}
using namespace std::placeholders;
void test2(){
    int num = 1000;
   auto f =  bind(func1, 1, _1 , _3 , std::cref(num),std::ref(num),num);
   //此时的num是10 ， 以及绑定进去了
   //注意 普通引用不能绑定const ref
   num =2000;
   f(20,30,40,50,60,70,80,20);
}
using std::function;

void test3(){
    //add:int(int ,int) => 绑定之后 int()
    function<int()> f1 = bind(add ,1,2);
    function<int(int,int)> f11 =add ;

    //multiply:int(int ,int,int) => 绑定之后 int()
    function<int()> f2 = bind(multiply ,1,2,3);
    function<int(int,int,int)> f21 =multiply;
    function<int(int)> f22 = bind(multiply ,1,2,3);  //由于绑定之后依旧可以传参

    function<int()> f3 = bind(&Point::add , Point(1,2).Data());

    // cout<<f1()<<endl;
    // cout<<f2()<<endl;
    // cout<<f22(2)<<endl; //调用时必须与类型相一致
    // cout<<f3()<<endl;

    int num = 1000;
    function<void(int,int,int)> f =  bind(func1, 1, _1 , _3 , std::cref(num),std::ref(num),num);

    function<int()> f4 = bind( &Point::_ix , Point(3,2).Data());
    cout<<f4()<<endl;;

    function<int()> f5 = bind( &Point::_ix , Point(6,2));
    cout<<f5()<<endl;;

    cout<<endl<<endl;
    Point p(2,3);
    
    function<double()> f6 = bind( &Point::add , p);
    cout<<f6()<<endl;;

    function<double()> f7 = bind( &Point::add , &p);
    cout<<f7()<<endl;;

    function<double(Point *)> f8 = bind( &Point::add , _1);
    cout<<f8(&p)<<endl;;
}

void test4(){
    int num = 1000;
    function<void(int,int,int)> f1 =  bind(func1, 1, _1 , _3 , 
                                        std::cref(num),std::ref(num),num);

    function<void(int,const char *,int)> f2 =  bind(func1, 1, _1 , _3 , 
                                        std::cref(num),std::ref(num),num);
    f2(1,"hwllo" , 3);
}
void test5(){
    int num = 1000;
    
    function<void(double&,int&)>f1 = [num](double &d , int &a  ){ //类型中的& 不能少
        cout<<d<<" "<<a<<endl;
    };
    double d = 2.3;
    int a =2;
    f1(d,a);
}
#include<vector>
#include<string>
using std::string;
std::vector< function<void(const string &)>>vec;

void test6(){
    int num = 100;
    string name("wangdao");
    vec.push_back([ &num,&name](const string&str  ){ 
        cout<<num<<" "<<name<<" "<<str<<endl;
    });
}

#endif

#if 0
#include<functional>
using std::function;
using std::bind;
class Figure1{
public:
        virtual void display() const = 0;
        virtual double area() const = 0;
};
class Rectanle1:public Figure1{ //通过继承实现多态
public:
    Rectanle1(double x ,double y):_length(x),_width(y){}
    void display()const override{
        cout<<"Rectangle ";
    }
    double area()const override{
        return _length*_width;
    }
private:
    double _length;
    double _width;
};
    
class Circle1:public Figure1{
public:
    Circle1(double x ):_radius(x){}
    void display()const override{
        cout<<"Circle  ";
    }
    double area()const override{
        return _radius*_radius*3.14;
    }
private:
    double _radius;
};
void func1(const Figure1 & fig){ //虚函数实现多态
    fig.display();
    cout<<fig.area();
    cout<<endl;
}
//////////////////
class Figure2{
public:
    using DisplayCallback = function<void()>  ;
    using AreaCallback = function<double()>;

    DisplayCallback _display;  //右值 ， 不能取地址
    AreaCallback _area;
    Figure2( DisplayCallback &&cb1 ,  AreaCallback &&cb2):
                        _display(std::move(cb1)),_area(std::move(cb2)){}

    //cb 右值引用 ， 可以接受/绑定/识别右值 ， 但是本身是左值
    void setDisplayCallback(DisplayCallback && cb){
        _display = std::move(cb);
    }
    void setAreaCallback(AreaCallback && cb){
        _area = std::move(cb);
    }
    void handleDispalyCallback()const{
        if( _display ){
            _display();
        }
    }
    double handleAreaCallback()const{
        if(_area){
            return _area();
        }else{
            return 0.0;
        }
    }

};

class Rectanle2{
    public:
        Rectanle2(double x ,double y):_length(x),_width(y){}
        void display()const {
            cout<<"Rectangle ";
        }
        double area()const {
            return _length*_width;
        }
    private:
        double _length;
        double _width;
};
class Circle2{
public:
    Circle2(double x ):_radius(x){}
    void display()const {
        cout<<"Circle  ";
    }
    double area()const {
        return _radius*_radius*3.14;
    }
private:
    double _radius;
};


void func2(const Figure2 & fig){ 
    fig.handleDispalyCallback();
    cout<<fig.handleAreaCallback()<<endl;
}
void test1(){
    Rectanle1 fig1(1,2);
    Circle1 fig2(2);
    func1(fig1);
    func1(fig2);


    Rectanle2 fig4(1,2);
    Figure2 fig3(bind(&Rectanle2::display,&fig4 ) , bind(&Rectanle2::area,&fig4 )) ;
    
    //fig3.setDisplayCallback( bind(&Rectanle2::display,&fig4 ));
    //fig3.setAreaCallback( bind(&Rectanle2::area,&fig4 ));
    func2(fig3);

    //Figure2 fig3;
    Circle2 fig5(2);
    // fig3.setDisplayCallback( bind(&Circle2::display,&fig5 ));
    // fig3.setAreaCallback( bind(&Circle2::area,&fig5 ));
    fig3.setDisplayCallback( [&fig5]() { fig5.display(); });
     fig3.setAreaCallback( [&fig5]() { return fig5.area(); });
    func2(fig3);

}
#endif
#if 0
#include<vector>
#include<functional>
#include<algorithm>
using namespace std::placeholders;
using std::vector;
using std::vector;
class Point{
public:
    Point(int x , int y):_ix(x),_iy(y){}
    
    void print()const{
        cout<<"( "<<_ix<<"  "<<_iy<<" )"<<endl;
    }

    int _ix = 0;
    int _iy = 0;

};
void test1(){
    vector<Point>vec{Point(2,3),Point(5,6)};
    std::for_each(vec.begin(), vec.end(),[](const Point&p){
        cout<<"( "<<p._ix<<"  "<<p._iy<<" )"<<endl;
    });

    std::for_each(vec.begin(), vec.end(),std::mem_fn(&Point::print));

    std::for_each(vec.begin(), vec.end(),bind(&Point::print,_1));

    std::function<void(Point)> f1 =  bind(&Point::print , _1);
    std::function<void(Point*)> f2 =  bind(&Point::print , _1);

    Point p(20,30);
    f1(p);
    f2(&p);
}
#endif
#if 1 
#include<memory>



void test1(){

}
#endif
int main(){
    test1();
    //string str = "hello";
    //vec[0](str);

    return 0;
}
