/*
 * @Author: rzk ruanzk2098@gmial.com
 * @Date: 2025-02-07 16:48:02
 * @LastEditors: rzk ruanzk2098@gmial.com
 * @LastEditTime: 2025-02-19 22:37:58
 * @FilePath: /cplusplus/src/stl.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AEiosr=
 * 
 */
#include<iostream>
using  std::cout;
using  std::endl;



#if 0 
#include <array>
using std::array;
template<class T>
void printArray(T & arr){
     for(auto &i : arr){
        cout<<i <<" ";
    }
    cout<<endl;
}
void test1(){
    array<int,10>arr1;
    printArray(arr1);

    array<int,10>arr2{};
    printArray(arr2);

    array<int,10>arr3{1,2,3,4};
    printArray(arr3);

}
#endif

#if 0
#include<vector>
using std::vector;
using std::size_t;

//三种遍历方式 
template<class T>
void print1(vector<T> &vec){
     for(auto& i:vec) 
        cout<<i<<" ";
    cout<<endl;
}

template<class T>
void print2(vector<T> &vec){
     for(size_t i = 0;i<vec.size();i++) 
        cout<<vec[i]<<" ";
    cout<<endl;
}

template<class T>
void print3(vector<T> &vec){
    typename vector<T>::iterator it ; // iterator
     for(it  =  vec.begin() ;it != vec.end();it++) 
        cout<<*it<<" ";
    cout<<endl;
}

void test0(){
    //五种构造方式
    vector<int> num1; //1 无参， 容器是空的
    //vector<int> num11(); // 函数声明  ， 创建空对象， 后面无需加() 
    //type name() ; 这是函数声明

    vector<int>num2(10,2); //2.  count 个value
    print1(num2);
    vector<int>num3(10); // count  个默认值
    print2(num3);

     int arr[10] = {0,1,2,3,4,5,6,7,9,9};
     vector<int>num4(arr , arr+10); //3.迭代器构造   左闭右开
     print3(num4);

    vector<int>num5(num2);  //4. 拷贝移动构造
    vector<int>num6(std::move(num3)); //num3 变空
    print2(num5);
    print2(num6);
    cout<<"11111"<<endl;
    print2(num3);
    cout<<"11111"<<endl;
    print2(num2);
    cout<<"11111"<<endl;
    cout<<endl;

    vector<int>num7{10 , 12}; // 5.initializer_list
    vector<int>num8 = {10 , 12}; //两种
    print2(num7);
}

void test1(){
    vector<int>num{1,2,3,4,5};
    display(num);
    num.push_back(6);
    num.push_back(7);
    display(num);
    num.pop_back();
    display(num);

    //vector<int>::pointer it = num.begin();
    // num.push_front(8);
    // num.push_front(9);
    // display(num);
    // num.pop_front();
    // display(num);
}

#endif

#if 0
#include<deque>
using std::deque;
using std::size_t;

//三种遍历方式 
template<class T>
void print1(deque<T> &vec){
     for(auto& i:vec) 
        cout<<i<<" ";
    cout<<endl;
}

template<class T>
void print2(deque<T> &vec){
     for(size_t i = 0;i<vec.size();i++) 
        cout<<vec[i]<<" ";
    cout<<endl;
}

template<class T>
void print3(deque<T> &vec){
    typename deque<T>::iterator it ; // iterator
     for(it  =  vec.begin() ;it != vec.end();it++) 
        cout<<*it<<" ";
    cout<<endl;
}

void test(){
    //五种构造方式
    deque<int> num1; //1 无参， 容器是空的
    deque<int> num11(); // 函数声明  ， 创建空对象， 后面无需加() 
    //type name() ; 这是函数声明

    deque<int>num2(10,2); //2.  count 个value
    print1(num2);
    deque<int>num3(10); // count  个默认值
    print2(num3);

     int arr[10] = {0,1,2,3,4,5,6,7,9,9};
     deque<int>num4(arr , arr+10); //3.迭代器构造   左闭右开
     print3(num4);

    deque<int>num5(num2);  //4. 拷贝移动构造
    deque<int>num6(std::move(num3)); //num3 变空
    print2(num5);
    print2(num6);
    cout<<"11111"<<endl;
    print2(num3);
    cout<<"11111"<<endl;
    print2(num2);
    cout<<"11111"<<endl;
    cout<<endl;

    deque<int>num7{10 , 12}; // 5.initializer_list
    deque<int>num8 = {10 , 12}; //两种
    print2(num7);

}
void test1(){
    deque<int>num{1,2,3,4,5};
    display(num);
    num.push_back(6);
    num.push_back(7);
    display(num);
    num.pop_back();
    display(num);

    
    num.push_front(8);
    num.push_front(9);
    display(num);
    num.pop_front();
    display(num);
}

#endif

#if 0
#include<list>
using std::list;
using std::size_t;

//三种遍历方式 
template<class T>
void print1(list<T> &vec){
     for(auto& i:vec) 
        cout<<i<<" ";
    cout<<endl;
}

// template<class T>
// void print2(list<T> &vec){
//      for(size_t i = 0;i<vec.size();i++) 
//         cout<<vec[i]<<" ";
//     cout<<endl;
// }

template<class T>
void print3(list<T> &vec){
    typename list<T>::iterator it ; // iterator
     for(it  =  vec.begin() ;it != vec.end();it++) 
        cout<<*it<<" ";
    cout<<endl;
}

void test(){
    //五种构造方式
    list<int> num1; //1 无参， 容器是空的
    list<int> num11(); // 函数声明  ， 创建空对象， 后面无需加() 
    //type name() ; 这是函数声明

    list<int>num2(10,2); //2.  count 个value
    print1(num2);
    list<int>num3(10); // count  个默认值
    print3(num3);

     int arr[10] = {0,1,2,3,4,5,6,7,9,9};
     list<int>num4(arr , arr+10); //3.迭代器构造   左闭右开
     print3(num4);

    list<int>num5(num2);  //4. 拷贝移动构造
    list<int>num6(std::move(num3)); //num3 变空
    print3(num5);
    print3(num6);
    cout<<"11111"<<endl;
    print3(num3);
    cout<<"11111"<<endl;
    print3(num2);
    cout<<"11111"<<endl;
    cout<<endl;

    list<int>num7{10 , 12}; // 5.initializer_list
    list<int>num8 = {10 , 12}; //两种
    print3(num7);

}
void test1(){
    list<int>num{1,2,3,4,5};
    display(num);
    num.push_back(6);
    num.push_back(7);
    display(num);
    num.pop_back();
    display(num);

    num.push_front(8);
    num.push_front(9);
    display(num);
    num.pop_front();
    display(num);
}
#endif

#if 0
#include<array>
#include<vector>
#include<deque>
#include<list>
using std::array;
using std::vector;
using std::deque;
using std::list;
namespace sequenceContainers{

template<class Container>
    void print(Container &con){
        typename Container::iterator it ; // iterator
         for(it  =  con.begin() ;it != con.end();it++) 
            cout<<*it<<" ";
        cout<<endl;
    }
template<class Container>
void print1(Container &con){
    typename Container::iterator it ; // iterator
    for(it  =  con.begin() ;it != con.end();it++) 
        cout<<*it<<" ";
    cout<<endl;
}

template<class Container>
void print2(Container &con){
    typename Container::iterator it ; // iterator
     for(it  =  con.begin() ;it != con.end();it++) 
        cout<<*it<<" ";
    cout<<endl<<endl;;
}
class Point{
public:
    Point(int x  ):_x(x){
        cout<<"Point(x)"<<x<<endl;;
    }
    Point(const Point &p ):_x(p._x){
        cout<<"Point(&p)"<<_x<<endl;;
    }
    Point(const Point &&p ):_x(p._x){
        cout<<"Point(&&p)"<<_x<<endl;;
    }
    Point & operator =(const Point &&p){
        _x = p._x;
        cout<<"operator =(const Point &&p)"<<_x<<endl;;
        return *this;
    }
    Point & operator =(const Point &p){
        _x = p._x;
        cout<<"operator =(const Point &&p)"<<_x<<endl;;
        return *this;
    }
    ~Point(){
        cout<<"~Point()"<<endl;
    }
    int _x;
   
};

void test1(){  //初始化
    vector<int>vec1;
    deque<int>deq1;
    list<int>l1;

    vector<int>vec2(3,4); 
    print(vec2);
    vector<int>vec3(3);
    print(vec3);
    deque<int>deq2(3,4);
    print(deq2);
    deque<int>deq3(3);
    print(deq3);
    list<int>l2(3,4);
    print(l2);
    list<int>l3(3);
    print(l3);

    vector<int>temp1{1,2,3,4,5,6};
    deque<int>temp2{1,2,3,4,5,6};
    list<int>temp3{1,2,3,4,5,6};

    vector<int>vec4(temp3.begin(), temp3.end()); 
    print(vec4);
    deque<int>deq4(temp3.begin(), temp3.end());
    print(deq4);
   
    list<int>l4(temp3.begin(), temp3.end());
    print(l4);
   

    int arr[5] = {2,4,6,8,10};
    vector<int>vec5(arr, arr+5); 
    print(vec5);
    
    deque<int>deq5(arr, arr+5);
    print(deq5);
   
    list<int>l5(arr, arr+5);
    print(l5);

    vector<int>vec6(temp1);
    deque<int>deq6(temp2);
    list<int>l6(temp3);

    //vector<Point>vec7 =  {Point(1,2)}; //
    //deque<int>deq7 {1,2,3,4};
    //list<int>l7 {1,2,3,4};

    // vector<int>vec7  {1,2,3,4};
    // deque<int>deq7{1,2,3,4};
    // list<int>l7= {1,2,3,4};
    //print(vec7);
    //print(deq7);
    //print(l7);
    //vector<Point>p1 (1, Point(2,3));

}
void test2(){
   vector<Point>vec1;
   vec1.reserve(5);
   vec1.push_back(2);
   vec1.emplace_back(3);
    cout<<"111111"<<endl;
    deque<Point>vec2;
   vec2.push_back(2);
   vec2.emplace_back(3);
    cout<<"111111"<<endl;

    list<Point>vec3;
   
   vec3.push_back(2);
   vec3.emplace_back(3);
       cout<<"111111"<<endl;

}
void test3(){
    vector<Point>vec1;
    vec1.reserve(5);
    
    vec1.emplace(vec1.begin(),2);
    cout<<"11111"<<endl;
    vec1.emplace(vec1.begin(),3);
}

void test4(){
    vector<Point>vec1;
    
    vec1.insert(vec1.begin(),2);
    cout<<"11111"<<endl;
    vec1.insert(vec1.begin(),3);
    cout<<"11111"<<endl;
    vec1.insert(vec1.begin(),4);
    cout<<endl<<endl;;
    vector<Point>vec2;
    
    vec2.insert(vec2.begin(),2);
    cout<<"11111"<<endl;
    vec2.insert(vec2.begin(),3);
    cout<<"11111"<<endl;
    vec2.insert(vec2.begin(),4);
}

void test5(){
    int arr[5] = {2,4,6,8};
    vector<int>vec(arr, arr+4); 

    vec.insert(vec.begin()+1, 1); //在第二个元素前面插
    print(vec);

    vec.insert(vec.begin()+1, 2,0); //在第二个元素前面插2个0
    print(vec);

    vec.insert(vec.begin()+1, arr,arr+3); //在第二个元素前面插3个元素
    print(vec);

    vec.insert(vec.begin()+1, {100,200,300}); //在第二个元素前面插3个元素
    print(vec);
}

void test6(){
     int arr[6] = {2,4,6,8,10,12};
    // deque<int>vec(arr, arr+4); 
    // vec.erase(vec.begin());
    // print(vec);
    // vec.erase(vec.begin() +2 , vec.end());
    // print(vec);

    list<int>vec(arr, arr+4); 
    list<int>::iterator it = vec.begin();
    //it = it +2; //
    it++;


}
void test7(){
     //int arr[6] = {2,4,6,8,10,12};

    vector<Point>vec{Point(1), Point(2)}; 
    cout<<"1111"<<endl;
    vec.clear();
    cout<<"1111"<<endl;
}
void test8(){

    vector<int>num1{1,3,5};
    vector<int>num2{2,4,6,8};
    print(num1);print(num2);

    num1.swap(num2);
    print(num1);print(num2);

    //num1.swap(vector<int>{0,0,0});

    //list<int>num3{0,0,0};
    //num1.swap(num3);

    num2.resize(20,0);
    print(num2);
    cout<<num2.size()<<" "<<num2.capacity()<<endl;

    num2.resize(3,0);
    print(num2);
    cout<<num2.size()<<" "<<num2.capacity()<<endl;

    cout<<num1.front()<<endl;;
    cout<<num1.back()<<endl;;

    num1.assign({0,0,0,0,0,0,0,0,0});
    print(num1);
    cout<<num1.size()<<" "<<num1.capacity()<<endl;

    cout<<&num1[0]<<endl;
    cout<<&(*num1.begin())<<endl;
    cout<<num1.data()<<endl;
}
void test9(){
    vector<int>num1{1,3,5};
    num1.reserve(10);
    cout<<num1.size()<<" "<<num1.capacity()<<endl;

    vector<int>num2{1,3,5,7,9};
    num2.reserve(2);
    cout<<num2.size()<<" "<<num2.capacity()<<endl;
}
//template<class T>

struct Compare{
    bool operator()(const int&t1 , const int& t2) const{
        return t1 > t2;
    }
};
void test10(){
    list<int>num1{1,5,3,2,9};
    print(num1);
  
    num1.sort();
    print(num1);

    list<int>num2{1,5,3,2,9};
    print(num2);
  
    num2.sort(Compare());
    print(num2);
    
    
    list<int>num3{1,5,3,2,9};
    print(num3);
  
    num3.sort(Compare());
    print(num3);
}

void test11(){
    list<int>num1{1,5,3,7,9};
    num1.sort();
    print(num1);
    list<int>num2{2,4,8,6,10};
    num2.sort();
    print(num2);
  
    num1.merge(num2);//num2 为空
    print(num1);
    print(num2); 

//,Compare()
}

void test12(){
    list<int>num1{1,3,5,7,9};
    list<int>num2{2,4,6,8,10};
    auto it1 = ++num1.begin();
    num1.splice(it1,num2 );//全部移动
    print1(num1); 
    print2(num2); //num2 移动完就空了


    list<int>num3{1,3,5,7,9};
    
    list<int>num4{2,4,6,8,10};
  
    auto it2 = ++num3.begin();
    num3.splice(it2,num4 , num4.begin());//移动某一个元素
    print1(num3); print2(num4);

    list<int>num5{1,3,5,7,9};
    
    list<int>num6{2,4,6,8,10};
  
    auto it3 = ++num5.begin();
    auto it4 = ++num6.begin();
    auto it5 = --num6.end();
    num5.splice(it3,num6 , it4,it5 );//移动范围
    print1(num5); print2(num6);
}

void test13(){
    list<int>num1{1,3,5,7,9,11,13};
   
    auto it1 = num1.begin();auto it2 = num1.end();
    it1++;
    it1++;
    it2--;
    it2--;

    num1.splice(it1,num1 , it2);//移动范围
    print1(num1); 
}
void test14(){
    constexpr int xy = 4;
 
    using Cell = std::array<int, 8>;
 
    array<Cell, xy * xy> board;

    board.fill({1,2,3,4,5,6,7,8}); // "";
 
    for( auto i: board){
        for(auto j:i){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}
}

#endif
#if 0 
#include<vector>
#include<set>
#include<string>
#include<map>
#include<utility>
using std::set;
using std::multiset;
using std::string;
using std::map;
using std::multimap;
using std::pair;
using std::vector;


class Point{
    public:
        Point(int x ,int y ):_x(x),_y(y){
            //cout<<"Point(x)"<<x<<endl;;
        }
        Point(const Point &p ):_x(p._x),_y(p._y){
            //cout<<"Point(&p)"<<_x<<endl;;
        }
        Point(const Point &&p ):_x(p._x),_y(p._y){
           // cout<<"Point(&&p)"<<_x<<endl;;
        }
        Point & operator =(const Point &&p){
            _x = p._x;
            _y = p._y;
            //cout<<"operator =(const Point &&p)"<<_x<<endl;;
            return *this;
        }
        Point & operator =(const Point &p){
            _x = p._x;
            _y = p._y;
           // cout<<"operator =(const Point &&p)"<<_x<<endl;;
            return *this;
        }
        // bool operator<(const Point &other) const{
        //     return (_x * _x + _y * _y) < (other._x * other._x + other._y * other._y);
        // }
        // bool operator>(const Point &other) const{
        //     return (_x * _x + _y * _y) > (other._x * other._x + other._y * other._y);
        // }
    
        friend std::ostream& operator<<(std::ostream & os, const Point & p);
        ~Point(){
            //cout<<"~Point()"<<endl;
        }
        int _x;
        int _y;
       
};
std::ostream& operator<<(std::ostream & os, const Point & p){
    os<<"( "<<p._x<<" "<<p._y<<" )  ";
    return os;
}

namespace std{
    template<>
    struct less<Point>
    {
        bool operator()(const Point & p1, const Point & other ){
            return (p1._x * p1._x + p1._y * p1._y) < (other._x * other._x + other._y * other._y);
        }
    };
}

namespace assoicativeTest{

template<class T>
void print1(T&st){
    for(auto& i: st) 
        std::cout << i << ' ';
    std::cout << '\n';
}

template<class T>
void print2(T&st){
    auto it = st.begin();
    for(;it != st.end();++it) 
        std::cout << *it << ' ';
    std::cout << '\n';
}




void test1(){
    set<int>st1;
    print1(st1);

    vector<int>vec{1,2,3,4,5,6,7};
    set<int>st2(vec.begin(),vec.end());
    //print(st2);
    
    // set<int>st3(st2);
    // print(st3);

    set<int>st4(std::move(st2));
    print2(st4);
    print2(st1);

    // set<int>st5{1,2,3,4,5,6};
    // print(st5);
}
void test2(){
    multiset<int>st1;
    print1(st1);

    vector<int>vec{1,2,3,4,5,6,7,3,4};
    multiset<int>st2(vec.begin(),vec.end());
    print1(st2);
    
    multiset<int>st3(st2);
    print1(st3);

    multiset<int>st4(std::move(st2));
    print2(st4);
    print2(st1);

    multiset<int>st5{1,2,3,4,5,6,6,6};
    print1(st5);
}


void test3(){
   
    vector<int>vec{1,2,3,4,5,6,7};
    set<int>st1(vec.begin(),vec.end());
    print1(st1);
    auto it = st1.find(4);
    if(it != st1.end() ){
        cout<<*it<<endl;
    }else{
        cout<<"not find "<<endl;
    }

    it = st1.find(10);
    if(it != st1.end() ){
        cout<<*it<<endl;
    }else{
        cout<<"not find "<<endl;
    }
}

struct Compare
{
    bool operator()(const Point & p1, const Point & other ){
        return (p1._x * p1._x + p1._y * p1._y) < (other._x * other._x + other._y * other._y);
    }
    /* data */
};





void test4(){
   
    vector<int>vec1{1,2,3,4,5,6,7};
    set<int>st1(vec1.begin(),vec1.end());
    print1(st1);
    
    pair<set<int>::iterator , bool>ret = st1.insert(4);
    print1(st1);
    if(ret.second){
        cout<<*ret.first<<endl;
    }else{
        cout<<"失败"<<endl;
    }

    vector<int>vec2{10,20,-1,4,30,40};
    st1.insert(vec2.begin(),vec2.end());
    print1(st1);

    // set<Point,Compare>st2{Point(1,2) ,Point(3,4)};
    // print1(st2);
    //cout<<Point(1,2)<<endl;
    //st2.insert(1,2);
    set<Point>st2{Point(1,2) ,Point(3,4)};
    print1(st2);
    st2.emplace(1,2);
}
void test5(){
   
    vector<int>vec1{1,2,3,4,5,6,7};
    set<int>st1(vec1.begin(),vec1.end());
    print1(st1);
    auto it1 = st1.begin();
    it1 ++;
    it1 ++; it1 ++;
    auto it2 = st1.erase(st1.begin());
    print1(st1);
    //cout<<*it2<<endl;
    size_t cnt = st1.erase(50);
    cout<<cnt<<endl;
    
    //* st1.begin() = 4;
}
struct Compare1 {
    bool operator()(const int& i, const int& j) const { 
        return i > j;  // 降序排序
    }
};

void test6(){
    vector<int>vec1{1,3,4,3,3,5,6,7};
    multiset<int>st1(vec1.begin(),vec1.end());
    print1(st1);

    auto it1 = st1.lower_bound(2);
    auto it2 = st1.upper_bound(2);

    cout<<*it1<<endl;
    cout<<*it2<<endl;

    while(it1 != it2){
        cout<<*it1<<" ";
        it1++;
    }
    cout<<endl;

    std::pair<multiset<int>::iterator ,multiset<int>::iterator>
    ret = st1.equal_range(3);
    while(ret.first != ret.second){
        cout<<*ret.first<<" ";
        ++ret.first;
    }
    cout<<endl;
    Compare1 c =Compare1();
    set<int,Compare1>st((Compare1()));
    st.insert(2);


}




}  
#endif 
#if 0 
#include<map>
#include<utility>
#include<string>
using std::map; 
using std::multimap;
using std::pair;
using std::make_pair;
using std::string;

template<class Container>
void print(const Container & con){
    for(auto &i :con ){
        cout<<i.first <<" "<<i.second<<"     ";
    }
    cout<<endl;
}

template<class Container>
void print1(const Container & con){
    for(auto it = con.begin(); it != con.end();++it ){
        cout<<it->first <<" "<<it->second<<"     ";
    }
    cout<<endl;
}

void test1(){

    map<int,string>num1;

    map<int,string>num2{pair<int , string> (1,"hefei"),
        pair<int , string> (2,"shanghai"),
        pair<int , string> (3,"taihe"),
        pair<int , string> (3,"beijing"),
        pair<int , string> (4,"shanghai"),
     };
    print(num2);

    map<int,string>num3{make_pair<int , string> (1,"hefei"),
                        make_pair<int , string> (2,"shanghai"),
                        make_pair<int , string> (3,"taihe") };
    print(num3);   

    map<int,string>num4{ {1,"hefei"},
        {2,"shanghai"},
        {3,"taihe"} };
    print(num4);

                        
    map<int,string>num5(num2);
    print(num5);
    map<int,string>num6(num2.begin(), --num2.end());
    print(num6);

    map<int,string,std::greater<int>>num7{ {1,"hefei"},
                                            {2,"shanghai"},
                                            {3,"taihe"} };
    print(num7);
    
}
void test2(){

    multimap<int,string>num1;

    multimap<int,string>num2{pair<int , string> (1,"hefei"),
        pair<int , string> (2,"shanghai"),
        pair<int , string> (3,"taihe"),
        pair<int , string> (3,"beijing"),
        pair<int , string> (4,"shanghai"),
     };
    print1(num2);

    multimap<int,string>num3{make_pair<int , string> (1,"hefei"),
                        make_pair<int , string> (2,"shanghai"),
                        make_pair<int , string> (3,"taihe") };
    print1(num3);   

    multimap<int,string>num4{ {1,"hefei"},
        {2,"shanghai"},
        {3,"taihe"} };
    print1(num4);

                        
    multimap<int,string>num5(num2);
    print1(num5);
    multimap<int,string>num6(num2.begin(), --num2.end());
    print1(num6);

    multimap<int,string,std::greater<int>>num7{ {1,"hefei"},
                                            {2,"shanghai"},
                                            {3,"taihe"} };
    print1(num7);

    cout<< num2.count(3)<<endl;;

    map<int, string>::iterator it =    num2.find(2);
    if(it!= num2.end()){
        cout<<"存在 "<<it->first<<"  " <<it->second<<endl;
    }else{
        cout<<"不存在"<<endl;
    }
    it = num2.find(6);
    if(num2.find(6) != num2.end()){

        cout<<"存在"<<it->first<<"  " <<it->second<<endl;

    }else{
        cout<<"不存在"<<endl;
    }

}

void test3(){
    map<int,string>num1{pair<int , string> (1,"hefei"),
        pair<int , string> (2,"shanghai"),
        pair<int , string> (3,"taihe"),
        pair<int , string> (3,"beijing"),
        pair<int , string> (4,"shanghai"),
     };
    print1(num1);

    pair<map<int,string>::iterator,bool>ret1 = num1.insert({5,"nanjingh"});
    print1(num1);
    if(ret1.second){
        cout<<"成功"<<endl;
        cout<< ret1.first->first<<" "<<ret1.first->second<<endl;
    }
    
    // pair<map<int,string>::iterator,bool>ret2 =  num1.emplace(make_pair(6, "shenzhen"));
    // print1(num1);
    // pair<map<int,string>::iterator,bool>ret3 =  num1.emplace(7, "guangzhou");
    // print1(num1);

    
    
    multimap<int,string>num2{pair<int , string> (1,"hefei"),
        pair<int , string> (2,"shanghai"),
        pair<int , string> (3,"taihe"),
        pair<int , string> (3,"beijing"),
        pair<int , string> (4,"shanghai"),
     };
    //print1(num2);

    // multimap<int,string>::iterator it = num2.insert({5,"nanjingh"});
    // //print1(num2);
    // map<int,string>::iterator it2 =  num2.emplace(make_pair(6, "shenzhen"));
    // print1(num2);
    // map<int,string>::iterator it3 =  num2.emplace(7, "guangzhou");
    // print1(num2);


}
// void fun(const map<int, string>&mp){
//     cout<<con[1] ;// error 
// }
void test4(){
    map<int,string>num1{pair<int , string> (1,"hefei"),
        pair<int , string> (2,"shanghai"),
        pair<int , string> (3,"taihe"),
        pair<int , string> (3,"beijing"),
        pair<int , string> (4,"shanghai"),
     };
    print1(num1);

    cout<<num1[4]<<endl;
    cout<<num1.at(3)<<endl;
    cout<<num1[6]<<endl;
    print1(num1);
    num1[6] = "ningxia";
    print1(num1);
    cout<<num1.at(7)<<endl;
    // map<int,int>num2{pair<int , int> (1,2),
    //     pair<int , int> (2,3),
    //     pair<int , int> (3,4),
    //     pair<int , int> (3,4),
    //     pair<int , int> (4,5),
    //  };
    // print1(num2);

    // cout<<num2[4]<<endl;
    // cout<<num2.at(3)<<endl;
    // cout<<num2[6]<<endl;
    // print1(num2);
    const map<int,int>num2{pair<int , int> (1,2),
            pair<int , int> (2,3),
            pair<int , int> (3,4),
            pair<int , int> (3,4),
            pair<int , int> (4,5)
         };
    //cout<<num2[4]<<endl;
    cout<<num2.at(3)<<endl;
    //cout<<num2[6]<<endl;
    print1(num2);
    
    multimap<int,string>num3{pair<int , string> (1,"hefei"),
        pair<int , string> (2,"shanghai"),
        pair<int , string> (3,"taihe"),
        pair<int , string> (3,"beijing"),
        pair<int , string> (4,"shanghai"),
     };
   

}
class Point{
    public:
        Point(int x ,int y ):_x(x),_y(y){
        }
        Point(const Point &p ):_x(p._x),_y(p._y){
        }
        Point(const Point &&p ):_x(p._x),_y(p._y){
        }
        Point & operator =(const Point &&p){
            _x = p._x;
            _y = p._y;
            return *this;
        }
        Point & operator =(const Point &p){
            _x = p._x;
            _y = p._y;
            return *this;
        }
        // bool operator<(const Point &other) const{
        //     cout<<"operator<(const Point &other)  "<<endl;
        //     return (_x * _x + _y * _y) < (other._x * other._x + other._y * other._y);
        // }

        // bool operator>(const Point &other) const{
        //     return (_x * _x + _y * _y) > (other._x * other._x + other._y * other._y);
        // }
    
        friend std::ostream& operator<<(std::ostream & os, const Point & p);
        ~Point(){
            //cout<<"~Point()"<<endl;
        }
        int _x;
        int _y;
       
};
std::ostream& operator<<(std::ostream & os, const Point & p){
    os<<"( "<<p._x<<" "<<p._y<<" )  ";
    return os;
}

// namespace std{
//     template<>
//     struct less<Point>
//     {
//         bool operator()(const Point & p1, const Point & other ){
//             //cout<<"less<>"<<endl;
//             return (p1._x * p1._x + p1._y * p1._y) < (other._x * other._x + other._y * other._y);
//         }
//     };
// }
struct Compare
{
    bool operator()(const Point & p1, const Point & other ){
        cout<<"Complar"<<endl;
        return (p1._x * p1._x + p1._y * p1._y) < (other._x * other._x + other._y * other._y);
    }
};
void test5(){
    map<int , Point>num1 = {{1 , Point(1,2)} ,
                           {2 , Point(3,4)}};
    print1(num1);
    map<Point , int ,Compare>num2 = { { Point(1,2) , 3} ,
                             { Point(3,4) ,7}};
    print1(num2);                   
 }
#endif
#if 0
#include<unordered_set>
#include<utility>
#include<string>
#include<vector>
using std::unordered_set; 
using std::pair;
using std::make_pair;
using std::string;
using std::vector;
template<typename Container>
void print(const Container& con){
    for(auto &elem: con){
        cout<<elem<<" ";
    }
    cout<<endl;
}
class Point{
    public:
        Point(int x ,int y ):_x(x),_y(y){
        }
        Point(const Point &p ):_x(p._x),_y(p._y){
        }
        Point(const Point &&p ):_x(p._x),_y(p._y){
        }
        Point & operator =(const Point &&p){
            _x = p._x;
            _y = p._y;
            return *this;
        }
        Point & operator =(const Point &p){
            _x = p._x;
            _y = p._y;
            return *this;
        }
        // bool operator<(const Point &other) const{
        //     cout<<"operator<(const Point &other)  "<<endl;
        //     return (_x * _x + _y * _y) < (other._x * other._x + other._y * other._y);
        // }

        bool operator==(const Point &other) const{
            return (_x ==  other._x)  &&  (_y ==  other._y) ;
        }
    
        friend std::ostream& operator<<(std::ostream & os, const Point & p);
        ~Point(){
            //cout<<"~Point()"<<endl;
        }
        int _x;
        int _y;
       
};
std::ostream& operator<<(std::ostream & os, const Point & p){
    os<<"( "<<p._x<<" "<<p._y<<" )  ";
    return os;
}

namespace std{
    template<>
    struct hash<Point>
    {
        size_t operator()(const Point & p1 ) const{ //const 不能省
            return p1._x+ p1._y;
        }
    };
    // template<>
    // struct equal_to<Point>
    // {
    //     bool operator()(const Point & p1 ,const Point & p2)const  {
    //         return (p1._x ==  p2._x)  &&  (p1._y ==  p2._y) ;
    //     }
    // };
}

struct myHash
{
    size_t operator()(const Point & p1 ) const{ //const 不能省
        // cout<<"my"<<endl;      
        return p1._x+ p1._y;
             
    }
};
struct myEqual
{
    bool operator()(const Point & p1 ,const Point & p2)const  {
        return (p1._x ==  p2._x)  &&  (p1._y ==  p2._y) ;
    }
};
void test1(){
    unordered_set<int>us;
    unordered_set<int>us1{1,2,3,4,5,6};
    print(us1);
    unordered_set<int>us2(us1);
    print(us2);
    vector<int>vec{1,2,3,4,5,6,7,8,9,0};
    unordered_set<int>us3(vec.begin(),vec.end());
    print(us3);

}

void test2(){
    unordered_set<Point> us1{Point(1,2), Point(3,4)};
    print(us1);

    unordered_set<Point, myHash> us2{Point(5,6), Point(7,8)};
    print(us2);

    // unordered_set<Point, myHash,myEqual> us3{Point(5,6), Point(7,8)};
    // print(us3);

    // unordered_set<Point, myHash,myEqual> us4{Point(5,6), Point(7,8)};
    // print(us4);

}
#endif 

#if 0 

#include<stack>
#include<vector>
#include<list>
#include<deque>
#include<queue>
#include<set>
using std::stack;
using std::vector;
using std::list;
using std::queue;
using std::deque;
using std::deque;
using std::priority_queue;
using std::cout;
using std::endl;

void test1(){
    
    stack<int>st1;
    stack<int,vector<int>>st2;
    stack<int,list<int>>st3;

    vector<int>vec{1,2,3,4,5,6,7};
    //stack<int>st4(vec);
    stack<int,vector<int>>st5(vec);
    //stack<int,vector<int>>st7(vec.begin(),vec.end());
    cout<<st5.top()<<endl;

    stack<int,vector<int>>st6(st5);
    //stack<int>st7(st5);
}
void test2(){
    
    priority_queue<int>qu1;
    priority_queue<int,deque<int>>qu2;

    vector<int>vec{1,2,6,8,11,6,7};
    deque<int>num{1,2,3,4,5,6,7};
    //priority_queue<int>qu3(vec);
    priority_queue<int,deque<int>>qu4(vec.begin() , vec.end());
    priority_queue<int,deque<int>>qu5(num.begin() , num.end());


    priority_queue<int,deque<int>>qu6(qu4);

    std::set<int>st{1,2,3,4};
    priority_queue<int,deque<int>>qu7(st.begin() , st.end());
    
}

#endif 
#if 0
#include<iterator>
#include<vector>
#include <algorithm>
#include <set>
#include <list>
#include<map>
#include<unordered_set>
using std::vector;
using std::ostream_iterator;
using std::istream_iterator;
using std::set;
using std::map;
using std::multimap;
using std::multiset;
using std::unordered_set;
using std::pair;
using std::cout;
using std::endl;
using std::copy;
void test1(){
    // vector<int>vec1{1,5,9,7,2};
    // //std::list<int>st{2,4,5,34,3,2,2,2,2};
    ostream_iterator<int> osit(cout," ");

    // std::copy(vec1.begin(),vec1.end(), osit);

    // for(auto& i: st){
    //     cout<<i<<" ";
    // }
    //cout<<endl; 
    vector<int>vec2;

    istream_iterator<int>isit(std::cin);
    //std::copy( isit, istream_iterator<int>() , vec2.begin() );

 
    std::copy( isit, istream_iterator<int>() , std::back_inserter(vec2));
    
    
    //std::copy( vec2.begin(), vec2.end() , osit );
    std::copy( vec2.begin(), vec2.end() , ostream_iterator<int>(cout," ") );
    cout<<"1111"<<endl;

    // unordered_set<int>unset{2,3,4,5,6,7};
    // unordered_set<int>::iterator it;
    // for (auto i = unset.begin(); i != unset.end(); i++) {
    //     //*i = 5;
    //     cout << *i << " ";
    // }
    //  multimap<int ,int>mp {{1,2},{1,3}};
    //  multimap<int ,int>::iterator it1 = mp.begin();
    //  multimap<int ,int>::iterator it2 = mp.begin();
    //  it2++;
    // //*it1 = (*it2);
    // cout<<std::is_copy_assignable<const int>::value<<endl;
    // pair<int,int>p(1,2);
    // it1->second = 20;
    // auto iiii = *it1;
}
#endif 

#if 0
#include<iterator>
#include<deque>
#include<vector>
#include<list>
#include <algorithm>

using std::deque;
using std::vector;
using std::back_inserter;
using std::back_insert_iterator;

using std::front_inserter;
using std::front_insert_iterator;

using std::inserter;
using std::insert_iterator;
using std::cout;
using std::endl;
using std::copy;

void test1(){
    deque<int>dq{1,2,3,4,5,6,7};

    std::list<int>ls{11,22,33,44,55,66};

    //copy(ls.begin() , ls.end(), back_inserter(dq));
    copy(ls.begin() , ls.end(), back_insert_iterator<deque<int>>(dq));
    copy(dq.begin() , dq.end(),std::ostream_iterator<int>(cout , " ") ); 
    cout<<endl;

    //copy(ls.begin() , ls.end(), front_inserter(dq));
    //copy(dq.begin() , dq.end(),std::ostream_iterator<int>(cout , " ") ); 

     auto it = dq.begin();
     it+=2;
     copy(ls.begin() , ls.end(), inserter(dq,it));
     copy(dq.begin() , dq.end(),std::ostream_iterator<int>(cout , " ") ); 
}
void test2(){
    deque<int>dq{1,2,3,4,5,6,7};
    back_inserter(dq) = 10;
    front_inserter(dq) = 100;
    auto it = dq.begin();
    it += 2;
    inserter(dq,it) = 1000;
    copy(dq.begin() , dq.end(),std::ostream_iterator<int>(cout , " ") ); 
}
void test3(){
    vector<int>dq{1,2,3,4,5,6,7};
    vector<int>::reverse_iterator rit = dq.rbegin();

    for(;rit != dq.rend();++rit){
        cout<<*rit<<" ";
    }
    cout<<endl;
}
#endif

#if 0
#include <algorithm>
#include<vector>
#include<iterator>
#include<algorithm>
#include<functional>
using std::vector;
using std::for_each;
using std::cout;
using std::endl;
void func(int &value){
    cout<<value++<<" ";
}

void test1(){
    vector<int>vec{1,4,7,9,5,2};

    //for_each(vec.begin() , vec.end() , func);
    for_each(vec.begin() , vec.end() , [](int value){
        cout<<value<<" ";
    });
    cout<<endl;
    //copy(vec.begin() , vec.end(),std::ostream_iterator<int>(cout , " ") ); 

}
void test2(){
    //[] : 
    int a = 100;
    //默认不能使用外作用域的变量 ， 需要捕获列表
    //默认const 类型的值传递 , 想修改： 引用传递 + 加 mutable 
    //
    []()->void{
        //bady
    }();
    [&a](int value){    //引用传递
        a++;    
        cout<<a<<" ";
        value++;
        cout<<value<<" ";
    }(200);
    cout<<endl;
    [a](int value) mutable->void{     //值传递， 修改的a 不应该外面的
        a++;    
        cout<<a<<" ";
        value++;
        cout<<value<<" ";
    }(200);
    cout<<endl;
    cout<<a<<endl;
    //copy(vec.begin() , vec.end(),std::ostream_iterator<int>(cout , " ") ); 

}
void test3(){
    //[] : 
    int a = 100;
    int b = 200;
    int c = 300;
    [&](){    //引用传递
        a++;    cout<<a<<" ";
        b++;    cout<<b<<" ";
        c++;    cout<<c<<" ";
    }();
    cout<<endl;
    cout<<a<<" ";
    cout<<b<<" ";
    cout<<c<<" ";


    cout<<endl;
    [=]() mutable{     //值传递， 修改的a 不应该外面的
        a++;    cout<<a<<" ";
        b++;    cout<<b<<" ";
        c++;    cout<<c<<" ";
       
    }();
    cout<<endl;
    cout<<a<<" ";
    cout<<b<<" ";
    cout<<c<<" ";
    cout<<endl;
    //copy(vec.begin() , vec.end(),std::ostream_iterator<int>(cout , " ") ); 
}

struct Point
{
    void print(int x , int y){
        auto x1 = [this,x,y]()->int{
            return _num + x + y;
        } ;
        x1();
    }
    int _num = 10; 
};

void test4(){
    vector<int>vec{1,4,7,2,6,3,9,0};
    auto it = std::remove_if(vec.begin() , vec.end() , [](int & value){ return value > 5;} );
    vec.erase(it, vec.end());

    
    for_each(vec.begin() , vec.end() , [](int & value){ 
                                                cout<<value<<" ";
                                            });
    cout<<endl;
}

void test5(){
    vector<int>vec{1,4,7,2,6,3,9,0};
    //auto it = std::remove_if(vec.begin() , vec.end() , bind1st(std::less<int>() , 5 ));
    auto it = std::remove_if(vec.begin() , vec.end() , bind2nd(std::greater<int>() , 5 ));
    vec.erase(it, vec.end());

    
    for_each(vec.begin() , vec.end() , [](int & value){ 
                                                cout<<value<<" ";
                                            });
    cout<<endl;
}
#endif

#if 0 
#include<typeinfo>
#include <boost/type_index.hpp>
void func2(int && i){
    cout<<"int && i"<<endl;
}

void func2(int & i){
    cout<<"int & i"<<endl;
}

template<class T >
void func1(T && a){ 
   //func2(std::forward<T&&>(t));
   cout<< boost::typeindex::type_id_with_cvr<T>().pretty_name()<<endl;
   cout<< boost::typeindex::type_id_with_cvr<decltype(a)>().pretty_name()<<endl;
}

void test1(){
    int i = 0;
    int &ref = i;
    
    func1(i); cout<<endl;

    func1(std::move(i)); cout<<endl;

    func1(ref);cout<<endl;
    func1(std::move(ref));cout<<endl;
}
/////////////////////////
void func3(int && i){
    cout<<"int && i"<<endl;
}

int func4(){
    //cout<<"int && i"<<endl;
    return 5;
}
void test2(){
    int a = 10;
    //foo(a);
    //func3(std::move(a));

    int &&ref1 = int(2);
    auto && ref2 = int(2);
    auto  ref3 = int(2);
    int b = int(2);
    cout<< boost::typeindex::type_id_with_cvr<decltype(ref2)>().pretty_name()<<endl;
    cout<< boost::typeindex::type_id_with_cvr<decltype(ref3)>().pretty_name()<<endl;
    //int & rref1 = int(2);
    const int c = 10;
    auto && ref4 = c;
    //int &ref5 = c;
}
template<class T >
void func5(T &a){ 
   //func2(std::forward<T&&>(t));
   cout<< boost::typeindex::type_id_with_cvr<T>().pretty_name()<<endl;
   cout<< boost::typeindex::type_id_with_cvr<decltype(a)>().pretty_name()<<endl;
}

template<class T >
void func6(const T &a){ 
    //func2(std::forward<T&&>(t));
    cout<< boost::typeindex::type_id_with_cvr<T>().pretty_name()<<endl;
    cout<< boost::typeindex::type_id_with_cvr<decltype(a)>().pretty_name()<<endl;
 }

template<class T >
void func7(T &&a){ 
   //func2(std::forward<T&&>(t));
   cout<< boost::typeindex::type_id_with_cvr<T>().pretty_name()<<endl;
   cout<< boost::typeindex::type_id_with_cvr<decltype(a)>().pretty_name()<<endl;
}

void test3(){
    int a = 10;
    int & ref = a;
    int && rref =std::move(a);
    func5(a);cout<<endl;
    func5(ref);cout<<endl;
    func5(rref);cout<<endl;
    func6(std::move(a));cout<<endl;


    func7(a);cout<<endl;
    func7(ref);cout<<endl;
    func7(std::move(a)); cout<<endl;
    func7(rref); 
    cout<<endl;
}
#endif

#if 0



// 接收左值的函数 f()
template<typename T>
void f(T &)
{
	cout << "f(T &)" << endl;
}

// 接收右值的函数f()
template<typename T>
void f(T &&)
{
	cout << "f(T &&)" << endl;
}
// 万能引用，转发接收到的参数 param
template<typename T>
void PrintType(T&& param)
{
	f(std::forward<T>(param));  // 将参数param转发给函数 void f()
}
int func1(){
    return 5;
}
void test1(){
    int a = 0;
	PrintType(a);//传入左值
	PrintType(int(0));//传入右值
    //int && ref = func1();
    //ref = 10;
}

#endif

#if 1

#include<functional>

using std::bind;
using std::bind1st;
int add(int x ,int y){return x+y;}
void test1(){
    auto f = bind(add ,1,2);
    cout<<f()<<endl;

}

#endif
int main(){
    //assoicativeTest::test6();
    test1();
    //int a = 0;

    //cout<< boost::typeindex::type_id_with_cvr<decltype(a)>().pretty_name()<<endl;

    //cout<<typeid(a).name()<<endl;
    // int a = 1, b =1;

    // int && ref1 = a+b;
    
    // int & ref2 = ref1;  //不能绑定左值
    
    //&ref1; //可以取地址
    
    return 0;
}

