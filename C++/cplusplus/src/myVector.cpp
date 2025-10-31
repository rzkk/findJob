
#include<iostream>
#include<algorithm>
#include <memory> 
using std::cout;
using std::endl;


template<class T>
class Vector{
public:
    Vector();
    ~Vector();
    typedef T* iterator;
    iterator begin(){
        return _start;
    }
    iterator end(){
        return _finish;
    }
    void push_back(const T&);

    void pop_back();


    int size();
    int capacity();
private:
    void reallocator();

    static std::allocator<T> _alloc;

    T* _start;           //第一个元素
    T* _finish;          //最后一个元素
    T* _end_of_storage;  // 空间末尾
};
template<class T>
std::allocator<T> Vector<T>::_alloc ;

template<class T>
Vector<T>::Vector(): _start(nullptr),_finish(nullptr), _end_of_storage(nullptr){}

template<class T>
Vector<T>::~Vector(){
    if(_start)
    {   
       //老空间上的销毁掉并回收
        while(_start != _finish){
            //_alloc.destroy(_start++);
            _alloc.destroy(--_finish);
        }
        
        _alloc.deallocate(_start , size());
    }
}

template<class T>
void Vector<T>::push_back(const T&value){
    if(size() == capacity()){
        //扩容
        reallocator();
    }
    _alloc.construct(_finish,value);
    ++_finish;  
}
template<class T>
void Vector<T>::pop_back(){
    if(size() > 0 )
        _alloc.destory(--_finish);

}
template<class T>
int Vector<T>::size(){
    return _finish - _start;
}
template<class T>
int Vector<T>::capacity(){
    return _end_of_storage - _start;
}


template<class T>
void Vector<T>::reallocator(){
    //申请新空间
    int oldCapacity = size();
    int newCapacity = oldCapacity > 0 ?2*oldCapacity :1;
    T * ptemp = _alloc.allocate(newCapacity); 
    
    if(oldCapacity )
    {   //拷贝a
       std::uninitialized_copy(_start,_finish, ptemp); //memory
           
        //老空间上的销毁掉并回收
        while(_start != _finish){
            //_alloc.destroy(_start++);
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start , oldCapacity);
    }
    //修改指针
    _start = ptemp;
    _finish = _start + oldCapacity;
    _end_of_storage = _start + newCapacity;
}


void test(){
    Vector<int> vec;
    for(int i = 0;i<10;i++){
        cout<<vec.size()<<" "<<vec.capacity()<<endl;
        vec.push_back(i);

    }
    for(auto & i : vec){  //auto 遍历需要iterator 支撑
        cout<<i<<"  ";
    }
    cout<<endl;
}



int main(){
    test();
}