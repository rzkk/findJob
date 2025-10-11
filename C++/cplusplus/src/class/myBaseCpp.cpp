#include"baseCpp.hpp"
#include<cstring>
#include<iostream>

int num = 100000000;
void Computer::setBrand(const char * brand){
    if(_brand != nullptr)
    {
        delete[] _brand;
    }
    _brand = new char[strlen(brand)+1]();
    strcpy(_brand , brand);
}
void Computer::setPrice(float price){
    _totalPrice -= _price;
    _price = price;
    _totalPrice += _price;
}
void Computer::showinfo() const{
    //std::cout<<"_brand 内容  "<<*((int*)_brand)<<"\n";
    //输出流运算符对char*指针有默认重载效果， 会去访问内容
    if(_brand)
    {
        std::cout<<"brand "<<_brand<<"  price "<<_price <<"  _totalPrice "<<_totalPrice<<std::endl;
    }else{
        std::cout<<"brand 空 "<<"  price "<<_price <<"  _totalPrice "<<_totalPrice<<std::endl;
    }
    //_brand = new char[2]();
    //_brand[0] = 'z';
    //pint = new int();
    //*pint = 2; 
    
}
void Computer::showinfo() {
    //std::cout<<"_brand 内容  "<<*((int*)_brand)<<"\n";
    //输出流运算符对char*指针有默认重载效果， 会去访问内容
    if(_brand)
    {
        std::cout<<"brand "<<_brand<<"  price "<<_price <<"  _totalPrice "<<_totalPrice<<std::endl;
    }else{
        std::cout<<"brand 空 "<<"  price "<<_price <<"  _totalPrice "<<_totalPrice<<std::endl;
    }
    
}
double Computer::_totalPrice = 0;
//double Computer::temp = 20;


void Point::setX(int x){
    _ix = x;
}
void Point::setY(int y){
    _iy = y;
}
void Point::print(){
    std::cout<<"( " <<_ix <<" , "<<_iy<<" )"<<std::endl;

    //std::cout<<_ref <<std::endl;
}

void  Line::print()
{
    _p1.print();
    std::cout<<"---->"<<std::endl;
    _p2.print();
}

Point2::Point2(const Point2 &p)	
{
	X = p.X;
	Y = p.Y;
	std::cout << "X = " << X << " Y=" << Y << "Point拷贝构造函数被调用" << std::endl;
}

Distance::Distance(const Point2 &xp1, const Point2 &xp2)
: p1(xp1)
, p2(xp2)
{
	std::cout << "Distance构造函数被调用" << std::endl;
	double x = double(p1.GetX() - p2.GetX());
	double y = double(p1.GetY() - p2.GetY());
	dist = sqrt(x * x + y * y);
}