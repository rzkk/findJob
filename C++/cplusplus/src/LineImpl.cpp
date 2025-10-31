
#include<iostream>
#include"pimpl.h"

using std::cout;
using std::endl;

class Line::LineImpl{
private:
    class Point{
    public:
        Point (int x ,int y):_ix(x),_iy(y){
            cout<<" Point() "<<endl;
        }
        
        void print(){
            cout<<" ( "<<_ix<<" , "<<_iy<<" ) ";
        }
        ~Point(){
            cout<<" ~Point() "<<endl;
        }
    private:
        int _ix;
        int _iy;
        static int _iz;
    };

public:
    LineImpl(int x1,int y1 , int x2 ,int y2 ):_p1(x1,y1),_p2(x2,y2){
        cout<<" LineImpl() "<<endl;
    } 
    ~LineImpl(){
        cout<<" ~LineImpl() "<<endl;
    };
   
    void printLine(){
        _p1.print();
        cout<<" -> ";
        _p2.print();
        cout<<endl;
    }
private:
    Point _p1;
    Point _p2;
   
};

Line::Line(int x1,int y1 , int x2 ,int y2 ): _pimpl(new LineImpl(x1, y1,x2 , y2)){
    cout<<" Line() "<<endl;
}

Line::~Line(){
    cout<<" ~Line() "<<endl;
    if(_pimpl){
        delete _pimpl;
        _pimpl = nullptr;
    }
    
}
void Line::printLine() const{
    _pimpl->printLine();
}