#include<iostream>
#include <string.h>

using std::cout;
using std::endl;
using std::size_t;

class String{
public:

    //不设为nullptr 省略了判空 ， 同时析构中是delete [] 
    String():_pstr(new char[1]()), _size(0){}

    String(const char * c):_pstr(new char[strlen(c)+1]()), _size(strlen(c)){
        strcpy(_pstr , c);
        cout<<"String(const char * c) "<<endl;
    }
    
    //左值
    String(const String & str):_pstr(new char[str._size+1]()), _size(str._size){
        strcpy(_pstr , str._pstr);
        cout<<"String(const String & str) "<<endl;
    }
    
    //右值
    String( String && str):_pstr(str._pstr), _size(str._size){
        str._pstr = nullptr;
        cout<<"String( String && str) "<<endl;
    }
    
    ~String(){
        if(_pstr){
            delete[] _pstr;
            _pstr = nullptr;
        }
        cout<<"~String()"<<endl;
    }

    
    String& operator=(const String& str){
        if(this != &str){  //todo 自复制
            if(_pstr){
                delete []_pstr;
            }
            _pstr = new char[str._size + 1]();
            strcpy(_pstr , str._pstr);
        }
        cout<<"String::operator=(const String& str)"<<endl;
        return *this;
    }

    String& operator=( String&& str){
        if(this != &str){

            if(_pstr) delete [] _pstr; //自己是不是空的， 体现在无参构造那块

            _pstr = str._pstr;
            str._pstr = nullptr;
        }
        cout<<"String::operator=( String&& str)"<<endl;
        return *this;
    }

private:
    char *_pstr;
    size_t _size;
};






int main(){
    //String s1("hello");

    //String s2 = s1;

    //String s3 = "hello";
    String("hell") = String("hell"); //两个临时变量

}