/*
 * @Author: rzk ruanzk2098@gmial.com
 * @Date: 2024-12-08 19:31:49
 * @LastEditors: rzk ruanzk2098@gmial.com
 * @LastEditTime: 2024-12-11 22:12:17
 * @FilePath: /cplusplus/src/myString.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AEc/
 * 
 */
#include "myString.h"
#include <string.h>

using std::cout;
using std::endl;
using std::size_t;

//不设为nullptr 省略了判空 ， 同时析构中是delete [] 
String::String():_pstr(new char[1]()), _size(0){}

String::String(const char * c):_pstr(new char[strlen(c)+1]()), _size(strlen(c)){
    strcpy(_pstr , c);
    cout<<"String(const char * c) "<<endl;
}

//左值
String::String(const String & str):_pstr(new char[str._size+1]()), _size(str._size){
    strcpy(_pstr , str._pstr);
    cout<<"String(const String & str) "<<endl;
}
//右值
String::String( String && str):_pstr(str._pstr), _size(str._size){
    str._pstr = nullptr;
    cout<<"String( String && str) "<<endl;
}

String::~String(){
    if(_pstr){
        delete[] _pstr;
        _pstr = nullptr;
    }
    cout<<"~String()"<<endl;
}

String& String::operator=(const String& str){
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

String& String::operator=( String&& str){
    if(this != &str){

        if(_pstr) delete [] _pstr; //自己是不是空的， 体现在无参构造那块

        _pstr = str._pstr;
        str._pstr = nullptr;
    }
    cout<<"String::operator=( String&& str)"<<endl;
    return *this;
}

String& String::operator=(const char * c){
        if(_pstr){   //默认构造中如果不是null, 这里就不用判空了
            delete []_pstr;
        }
        _pstr = new char[strlen(c) + 1]();
        strcpy(_pstr , c);
    cout<<" String::operator=(const char * c)"<<endl;
     //   *this = String(c);
    return *this;
}

String & String::operator+=(const String& s){
    _size += s._size;

    char * temp = _pstr;

    _pstr = new char[_size+1]();
    strcat(_pstr, temp );
    strcat(_pstr, s._pstr);
    if(temp){
        delete[] temp;
    }
    return *this ;
}

String & String::operator+=(const  char * c){
    _size += strlen(c);

    char * temp = _pstr;

    _pstr = new char[_size+1]();
    strcat(_pstr, temp );
    strcat(_pstr, c);
    if(temp){
        delete[] temp;
    }
    return *this ;
}

char & String::operator[](size_t index){
    if(index < _size){  //后面还有个 \0
        return _pstr[index];
    }else{
        cout<<"out of range "<<endl;
        static char nullchar = '\0';
        return nullchar;
    }
}
//const  对象只能调用const成员
const char & String::operator[](size_t index) const {
    if(index < _size){  //_size 不包含 \0  
        return _pstr[index];
    }else{
        //cout<<"\n"<<_size<<"  "<<index <<" out of range  ";
        std::cout<<"out of range "<<endl;
        static char nullchar = '\0';
        return nullchar;
    }
}

std::size_t String::size()const{
    return _size;
}


const char* String::c_str() const{
    return _pstr;
}


bool operator==(const String &s1,const String &s2){
    return strcmp(s1.c_str(),s2.c_str()) == 0;
}

bool operator!=(const String &s1,const String &s2){
    return strcmp(s1.c_str(),s2.c_str()) != 0;
}

bool operator<(const String &s1,const String &s2){
    return strcmp(s1.c_str(),s2.c_str()) < 0;
}
bool operator>(const String &s1,const String &s2){
    return strcmp(s1.c_str(),s2.c_str()) > 0;
}

bool operator<=(const String &s1,const String &s2){
    return strcmp(s1.c_str(),s2.c_str()) <= 0;
}
bool operator>=(const String &s1,const String &s2){
    return strcmp(s1.c_str(),s2.c_str()) >= 0 ;
}

std::ostream &operator<<(std::ostream &os, const String &s){
    if(s._pstr )   
        os<<s._pstr;
    return os;
}
std::istream &operator>>(std::istream &is, String &s){
        if (s._pstr) {
        delete[] s._pstr;
        s._size = 0;
    }

    size_t capacity = 2;  // 初始容量
    s._pstr = new char[capacity]();  // 分配内存

    char ch;
    while (is.get(ch) && ch != '\n') {
        if (s._size  + 1 >= capacity) {  // 需要扩容时
            capacity *= 2;
            char* temp = new char[capacity]();
            strcpy(temp, s._pstr);
            delete[] s._pstr;
            s._pstr = temp;
        }
        s._pstr[s._size++] = ch;
    }
    s._pstr[s._size] = '\0';  // 确保以 '\0' 结尾
    if (s._size+1 < capacity) {
        char* temp = new char[s._size+1]();  //strcpy 复制的时候不管你申请的内存够不够 ， 都会一股脑复制
        strcpy(temp, s._pstr);
        delete[] s._pstr;
        s._pstr = temp;
    }
    return is;
}