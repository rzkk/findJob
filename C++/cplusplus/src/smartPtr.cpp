#include<iostream>

#include<memory>

using std::auto_ptr;
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
using std::cout;
using std::endl;


#if 0
//auto_ptr
void test(){
    auto_ptr<int> ap1 (new int (10));
    cout<< *ap1 <<endl;;
    
    auto_ptr<int> ap2 (ap1);
    cout<<ap2.get()<<endl;   //返回资源的指针
    cout<<ap1.get()<<endl;
    //cout<<*ap1<<endl; //ap1 中的资源指针置空了
    cout<<*ap2<<endl;
    cout<<"111111111"<<endl;
}
#endif

////////////
//unique_ptr
#if 0
class Point{
public:
Point() = default;
    Point(int x,int y):_ix(x),_iy(y){
       // cout<<"Point(int ,int)"<<endl;
    }
    void print()const{
        cout<<_ix <<" "<<_iy<<endl;
    }
private:
    int _ix;
    int _iy;

};

#include<vector>
using std::vector;
void test(){
    unique_ptr<int> up1 (new int (10));
    cout<< *up1 <<endl;;
    
    unique_ptr<int>up2 (new int (100));

    up2 = std::move(up1);
    cout<<*up2<<endl;
    //cout<<*up1<<endl;
    unique_ptr<int> up3 ( std::move(up2));
    cout<<*up3<<endl;


    unique_ptr<Point>upPoint1(new Point(1,2));

    // upPoint1->print();
    // (*upPoint1).print();

    unique_ptr<Point>upPoint2(new Point(3,4));
    unique_ptr<Point>upPoint3(new Point(5,6));

    //这里unique 不允许复制 
     vector<unique_ptr<Point>> vecuPoint1;

//     //std::initializer_list<unique_ptr<Point>> ll (std::move(upPoint1));
    
     //vector<unique_ptr<Point>> vecuPoint2;
     vecuPoint1.push_back(std::move(upPoint1)); 
     //vecuPoint1.push_back(upPoint2);
     vecuPoint1.push_back(unique_ptr<Point>(new Point(1,2)));
     //存到vec中的元素是副本 ，  unique_ptr(const unique_ptr&) = delete;




    vecuPoint1[1]->print();
//     upPoint1->print();  // 经过移动之后 底层指针变成空的了

    //unique_ptr<Point>up(std::move(upPoint1));
    //unique_ptr<Point> && up = std::move(upPoint1);
    //upPoint1->print();
}



// void test(){
    
    // unique_ptr<Point>upPoint1(new Point(1,2));

    // unique_ptr<Point>upPoint2(new Point(3,4));

    // vector<unique_ptr<Point>> vecuPoint1{std::move(upPoint1) ,std::move(upPoint2) };

    // vector<unique_ptr<Point>> vecuPoint2{unique_ptr<Point>(new Point(1,2))};
// }
#endif

//////
//shared_ptr
#if 0 
#include<vector>
using std::vector;
class Point{
public:
Point() = default;
    Point(int x,int y):_ix(x),_iy(y){
       // cout<<"Point(int ,int)"<<endl;
    }
    void print()const{
        cout<<_ix <<" "<<_iy<<endl;
    }
private:
    int _ix;
    int _iy;

};

void test1(){
    shared_ptr<int>sp1(new int(20));
    cout<<*sp1<<endl;
    cout<<sp1.get()<<endl; 

    shared_ptr<Point>sp2(new Point(1,2)); 
    sp2->print(); 
    (*sp2).print();
    cout<<sp2.use_count()<<endl;;
    shared_ptr<Point>sp3(sp2);
    cout<<sp2.use_count()<<endl;
    cout<<sp3.use_count()<<endl;
    cout<<sp2.get()<<endl;;  //共管资源
    cout<<sp3.get()<<endl;

    sp3.reset(new Point(3,4));  //原本资源的引用计数减一 ， sp3 重新管理新的资源
    sp3->print();
    cout<<sp2.use_count()<<endl;
    cout<<sp3.use_count()<<endl;
    cout<<sp2.get()<<endl;;  //共管资源
    cout<<sp3.get()<<endl;

    ///////////
    shared_ptr<Point>sp4(new Point(1,2)); 
    sp4 = sp2;    //共管资源
    cout<<sp2.use_count()<<endl; 
    cout<<sp4.use_count()<<endl;
    cout<<sp2.get()<<endl;;  
    cout<<sp4.get()<<endl;
}
void test2(){
    vector<shared_ptr<Point>>vec;
    shared_ptr<Point>sp1(new Point(1,2)); 
    shared_ptr<Point>sp2(new Point(3,4)); 
    shared_ptr<Point>sp3(new Point(5,6)); 
    shared_ptr<Point>sp4(new Point(7,8)); 
    vec.push_back(sp1);
    cout<<sp1.use_count()<<endl;;  //2 ， vec中有个副本
    (*vec[0]).print();

    vec.push_back(sp2);

    vec.push_back(std::move(sp3)); //sp3 丧失管理权
    cout<<sp3.use_count()<<endl;

     (*vec[2]).print();
     //sp3->print();
    vec.push_back(std::move(sp1));
    //cout<<sp1.use_count()<<endl;;
    cout<<vec[0].use_count()<<endl;;

}

class Child;

class Parent{
public:
    Parent(){
        cout<<"Parent()"<<endl;
    }
    ~Parent(){
        cout<<"~Parent()"<<endl;
    }
    //shared_ptr<Child>_spChild;  //循环引用的问题 , 解决其中一个改成weakptr
    weak_ptr<Child>_spChild;  //
};

class Child{
public:
    Child(){
        cout<<"Child()"<<endl;
    }
    ~Child(){
        cout<<"~Child()"<<endl;
    }
    shared_ptr<Parent> _spParent;
    //weak_ptr<Parent> _spParent;
};

void test3(){  //循环引用
    shared_ptr<Parent>parentPtr(new Parent());
    shared_ptr<Child>childPtr(new Child());
 
    cout<<parentPtr.use_count()<<endl;;
    cout<<childPtr.use_count()<<endl<<endl;;;

    parentPtr->_spChild = childPtr;   //复制是共享管理权
    childPtr->_spParent = parentPtr;

    cout<<parentPtr.use_count()<<endl;
    cout<<childPtr.use_count()<<endl;

}
void test4(){  //循环引用
    shared_ptr<Parent>parentPtr(new Parent());
    shared_ptr<Child>childPtr(new Child());
 
    cout<<parentPtr.use_count()<<endl;;
    cout<<childPtr.use_count()<<endl<<endl;;;

    //sharedptr 可以给 weakptr 赋值
    parentPtr->_spChild = childPtr;   //复制是共享管理权
    childPtr->_spParent = parentPtr;

    cout<<parentPtr.use_count()<<endl;
    cout<<childPtr.use_count()<<endl;

}

void test5(){
    shared_ptr<int>sp1(new int(10));
    weak_ptr<int>wp1(sp1);
    weak_ptr<int>wp2();
    wp1.use_count();
    //weak_ptr<int>wp3(new int);
    weak_ptr<int>wp3;


    cout<<wp1.use_count()<<endl;

    shared_ptr<int> sp2 = wp1.lock();
    wp1.lock();
    cout<<wp1.use_count()<<endl;

    if(wp1.lock()){
        cout<<"wp1.lock()"<<endl;
    }

}
#endif

#if 0 
#include<string>
using std::string ;

struct FILEDelete
{
    void operator()(FILE* p){
        if(p){
            fclose(p);
            cout<<"FILEDelete :fclose() "<<endl;
        }    
    }
};


void test1(){  //原始方法 ， 手动关闭
    string str = "hello world\n";
    FILE* fp = fopen("temp.txt","a+");
    fwrite(str.c_str() , 1,  str.size() , fp);
    fclose(fp);
}

void test2(){
    string str = "hello world\n";
    //FILE* fp = fopen("temp.txt","a+");
    unique_ptr<FILE , FILEDelete>up(fopen("temp.txt","a+"));
    //get() 从智能指针中拿出裸指针
    fwrite(str.c_str() , 1,  str.size() , up.get()); 
    //没有执行fclose , 缓冲区没有刷新
}
void test3(){
    string str = "hello world\n";
    //FILE* fp = fopen("temp.txt","a+");
    FILEDelete deleter;
    //shared_ptr<FILE>up(fopen("temp.txt","a+") , FILEDelete() );
    shared_ptr<FILE>up(fopen("temp.txt","a+") , deleter);
    //get() 从智能指针中拿出裸指针
    fwrite(str.c_str() , 1,  str.size() , up.get()); 
    //没有执行fclose , 缓冲区没有刷新
}



#endif
#if 0  //误用 1 
class Point{
public:
Point() = default;
    Point(int x,int y):_ix(x),_iy(y){
       // cout<<"Point(int ,int)"<<endl;
    }
    void print()const{
        cout<<_ix <<" "<<_iy<<endl;
    }
   
private:
    int _ix;
    int _iy;

};

void test1(){
    Point * p1 = new Point(1,2);
    unique_ptr<Point>up1 (p1);
    unique_ptr<Point>up2 (p1);

}
void test2(){
    Point * p1 = new Point(1,2);
    shared_ptr<Point>up1 (p1);
    shared_ptr<Point>up2 (p1);

    cout<<up1.use_count()<<endl;;
}
#endif
#if 1  // 误用 2 

class Point : public std::enable_shared_from_this<Point>{
public:
Point() = default;
    Point(int x,int y):_ix(x),_iy(y){
       // cout<<"Point(int ,int)"<<endl;
    }
    void print()const{
        cout<<_ix <<" "<<_iy<<endl;
    }
    // shared_ptr<Point> addPoint(Point * pt){
    //     _ix += pt->_ix;
    //     _iy += pt->_iy;
    //     //return shared_ptr<Point>(this); //这里也是通过裸指针创建
    // }
    
    shared_ptr<Point> addPoint(Point * pt){
        _ix += pt->_ix;
        _iy += pt->_iy;
        //合法方式获得一个*this 资源的sharedPtr 
        return shared_from_this(); //这里也是通过裸指针创建
    }
private:
    int _ix;
    int _iy;

};
void test(){

    shared_ptr<Point>sp1 (new Point(1,2));
    shared_ptr<Point>sp2 (new Point(1,2));

    shared_ptr<Point>sp3 ( sp1->addPoint(sp2.get()));

    cout<<sp1.use_count()<<endl;;
    cout<<sp2.use_count()<<endl;;
    cout<<sp3.use_count()<<endl;;
    cout<<endl;
    cout<<sp1.get()<<endl;;
    cout<<sp2.get()<<endl;;
    cout<<sp3.get()<<endl;;
}
#endif

int main(){
    test();
} 



class Point : public std::enable_shared_from_this<Point>{
public:
Point() = default;
    Point(int x,int y):_ix(x),_iy(y){
       // cout<<"Point(int ,int)"<<endl;
    }
    shared_ptr<Point> addPoint(Point * pt){
        _ix += pt->_ix;
        _iy += pt->_iy;
   
        return shared_from_this(); 
    }
private:
    int _ix;
    int _iy;

};

void test(){
    shared_ptr<Point>sp1 (new Point(1,2));
    shared_ptr<Point>sp2 (new Point(1,2));

    shared_ptr<Point>sp3 ( sp1->addPoint(sp2.get()));
}

