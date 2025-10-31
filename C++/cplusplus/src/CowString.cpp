/*
 * @Author: rzk ruanzk2098@gmial.com
 * @Date: 2024-12-12 19:44:03
 * @LastEditors: rzk ruanzk2098@gmial.com
 * @LastEditTime: 2024-12-14 12:51:47
 * @FilePath: /cplusplus/src/CowString.cpp
 * @Description: 这是默认设置,请设置`customMade`, 
 * 打开koroFileHeader查看配置 进行设置: 
 * https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include<iostream>
#include"CowString.h"
#include<string.h>

using std::cout;
using std::endl;
using std::size_t;

CowString::CowString() : _pstr(mallocCowString()){
   initRefCount();
}
CowString::CowString(const char * p) : _pstr(mallocCowString(p)){
    strcpy(_pstr, p);
    initRefCount();
}
CowString::CowString(const CowString & rhs) : _pstr(rhs._pstr){
   increaseRefCount();
}

CowString::~CowString() {
    releaseCowString();
}       
CowString & CowString::operator=(const CowString & rhs){
    if(this != &rhs){
        releaseCowString();  // 尝试回收堆
        _pstr = rhs._pstr;  // 浅拷贝
        increaseRefCount();
    }
    return *this;
}

char& CowString::CharProxy::operator=(const char  rhs){

        if(_index >= 0 && _index < _self.size()) {  // 
            if(_self.getRefCount() > 1){   //相当于新生
                _self.decreaseRefCount();
                char * temp = _self.mallocCowString(_self._pstr);
                strcpy(temp ,_self. _pstr);
                _self._pstr = temp;
                _self.initRefCount();
            }
            _self._pstr[_index] = rhs;
            return _self._pstr[_index]; 
        }else{
            cout<<"out of range"<<endl;
            static char nullchar = '\0';
            return nullchar;
        }
}
ostream& operator<< (ostream & os, const CowString::CharProxy &rhs){
 
        if(rhs._index >= 0 && rhs._index < rhs._self.size()) {  // 
            os<<rhs._self._pstr[rhs._index ];
        }else{
            os<<"out of range"<<endl;

        }
        return os;
}      

//返回str1[0]
//为了区别返回的对象是进行读操作还是写操作， 所以返回的要是一个代理对象 ， 其只能用str1, index 创建
//要返回的是一个代理对象 ， 临时的 ， 因此不能返回引用
//同时 要返回的代理对象还要影响包含原来的CowString , 考虑引用成员变量
CowString::CharProxy CowString::operator[](size_t index ){
        return CharProxy(*this , index); //这里尽管是返回的局部变量 ，但是这个局部变量中的self 是*this本的引用
        //return CharProxy(this , index); //这里用指针也可以，也可以实现，但是C++推荐使用引用 
}


ostream & operator<<(ostream & os ,const  CowString & rhs){
    if(rhs._pstr)
        os<<rhs._pstr;
    return os;
}
size_t CowString::size() const{
     return strlen(_pstr); 
}
void CowString::initRefCount(){
    *(int*)(_pstr - kRefCountLength) = 1;
}
void CowString::increaseRefCount(){
    ++*(int*)(_pstr - kRefCountLength);
}
void CowString::decreaseRefCount(){
    --*(int*)(_pstr - kRefCountLength);
}
char * CowString::mallocCowString(const char * p )
{
    if(p){
        return new char[strlen(p) + kRefCountLength +1]() + kRefCountLength;
    }else {
        return new char[ kRefCountLength +1]() + kRefCountLength;
    }
}
void CowString::releaseCowString(){
    decreaseRefCount();
    if(getRefCount() == 0){
        delete [] (_pstr -kRefCountLength);
        _pstr = nullptr;
        cout<<">>>>>> delete  heap "<<endl;
    }
}