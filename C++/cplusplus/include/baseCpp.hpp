#ifndef _BASECPP_H
#define _BASECPP_H
#include<cstring>
#include<iostream>
#include<cmath>
class Computer{
public:
    Computer():_brand(nullptr), _price(0) {}
    Computer(const char* brand ,double price ):_brand(new char[strlen(brand) +1]()) , _price(price){
        strcpy(_brand , brand);

        _totalPrice +=  _price;
    }
    Computer(const Computer&c):_brand(new char[strlen(c._brand)+1]()) ,_price(c._price){
        strcpy(_brand, c._brand);
        _totalPrice +=  _price;
    }

    Computer& operator= (const Computer&c)
    {
        if(this != &c){
            if(_brand != nullptr)
            {
                delete[] _brand;
            }
            _brand = new char[strlen(c._brand)+1]();
            strcpy(_brand, c._brand);

            _totalPrice -= _price;
            _price = c._price;
            _totalPrice +=  _price;
        }
        return *this ;
    }
    ~Computer(){
        //std::cout<<"析构 "<<_brand<<std::endl;
        if(_brand)
        {
            delete[] _brand;
            this->_brand = nullptr;  //安全回收
        } 
        _totalPrice -= _price;
    }
    void setBrand(const char * brand);
   
    void setPrice(float price);
   
    void showinfo() const;
    void showinfo();
    static void printTotalPrice()
    {
        std::cout<<"totalPrice "<< _totalPrice<<std::endl;
    }
    //static double temp; 
private:
    char* _brand;
    double _price;  
    static double _totalPrice; 
    const int *pint;
};



extern int num;
// class Point {
// public:
//     Point():_ix(0),_iy(0),_ref(num){}
//     Point(int x ,int y ,int z ):_ix(x),_iy(y),_ref(z){}
       
//     void setX(int x);
//     void setY(int y); 
//     void print();

// private:
//     int _ix;
//     int _iy;
//     int &_ref;
//     //int *pint;
//     //Computer c1;
// };
class Point {
public:
    Point():_ix(0),_iy(0){}
    Point(int x ,int y ):_ix(x),_iy(y){
        std::cout<<"有参"<<std::endl;
    }
    Point(const Point &p):_ix(p._ix),_iy(p._iy)
	{
		std::cout<< "拷贝构造函数被调用" << std::endl;
	}

    void setX(int x);
    void setY(int y); 
    void print();

private:
    int _ix;
    int _iy;
};

class Line{
public:
    Line()=default;
    Line(int x1, int x2, int x3,int x4):_p1(x1,x2), _p2(x3,x4){}

    Line(Point p1, Point p2):_p1(p1), _p2(p2){}
    void print();
private:
    Point _p1 ;
    Point _p2 ;  
};


class Point2	
{
public:
    Point2(int xx = 0, int yy = 0) 
	{
		X = xx;
		Y = yy;
		std::cout << "point构造函数被调用" << std::endl;
	}
	

   	Point2(const Point2 &p);
   	
   	int GetX() 
   	{
   		return X;
   	}
   	
   	int GetY() 
   	{
   		return Y;
   	}

private:
	int X,Y;
};



class Distance	
{
public:	
	Distance(const Point2 &xp1, const Point2 &xp2);
	double GetDis()
	{
		return dist;
	}
private:	
	Point2 p1,p2;
	double dist;	
};


class Student{
public:
    Student(int id , const char * name ):_id(id) , _name(new char[strlen(name)+1]())
    {
        strcpy(_name , name);
        std::cout<<"Student  \n";
    }
    // ~Student()
    // {
    //     if(_name)
    //     {
    //         delete[] _name;
    //         _name = nullptr;
           
    //     }
    //      std::cout<<"~Student \n";
    // }

    void * operator new(size_t sz)
    {
        void * ret  = malloc(sz);
        std::cout<<"operator new \n";
        return ret;
    }

    // void operator delete(void * pointer){
    //     std::cout<<"operator delete \n";
    //     free(pointer);
    // }

    void print()
    {
        std::cout<<_name<<"  "<<_id<<std::endl;;
    }
private:
 ~Student()
    {
        if(_name)
        {
            delete[] _name;
            _name = nullptr;
           
        }
         std::cout<<"~Student \n";
    }
    // void operator delete(void * pointer){
    //     std::cout<<"operator delete \n";
    //     free(pointer);
    // }
    int _id;
    char * _name;
};








#endif 