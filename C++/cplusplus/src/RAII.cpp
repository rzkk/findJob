#include<iostream>

using std::cout;
using std::endl;

class Point{
public:
    Point(int x , int y):_ix(x) , _iy(y){}
    void print(){
        cout<<"( "<<_ix<<", "<<_iy<<" )"<<endl;
    }
private:
    int _ix;
    int _iy;
};

template<class T>
class RAII{
public:
    //构造函数中初始化资源
    RAII(T *data):_data(data){
        cout<<"RAII(T *data)"<<endl;
    }
    //析构中释放资源
    ~RAII(){
        if(_data){
            delete _data;
            _data = nullptr;
        }
        cout<<"~RAII()"<<endl;
    }
    //访问资源方法
    T * operator->(){
        return _data;
    }
    T & operator*(){
        return *_data;
    }
    T*get(){
        return _data;
    }
    void set(T*data){
        if(_data){
            delete _data;
            _data = nullptr;
        }
        _data = data;
    }
    //不允许复制 赋值
    RAII(const RAII& ) = delete;
    RAII&operator=(const RAII& ) = delete;
private:
    T * _data;
};

void test(){
    RAII<Point>ra(new Point(2,3));
    ra->print();
}


int main(){
    test();
}