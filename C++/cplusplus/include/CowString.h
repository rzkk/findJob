/*
 * @Author: rzk ruanzk2098@gmial.com
 * @Date: 2024-12-12 19:46:41
 * @LastEditors: rzk ruanzk2098@gmial.com
 * @LastEditTime: 2024-12-14 11:11:05
 * @FilePath: /cplusplus/include/CowString.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _COWSTRING_H_
#define _COWSTRING_H_

#include<iostream>

using  std::ostream;

class CowString{
private:
    class CharProxy{  // 友元而已 
    public:
        //为了代理对象能影响CowString对象，用引用
        CharProxy( CowString &self ,std::size_t index) :_self(self) , _index(index){}
        char& operator=( const char  rhs);
        friend ostream& operator<< (ostream & os, const CharProxy &c);

    private:
        //CowString self;  //不允许使用不完整的类型 "CowString"
        CowString &_self; 
        std::size_t _index;
    };
public:
    CowString();
    CowString(const char *);
    CowString(const CowString &);
    
    ~CowString();
    CowString & operator = (const CowString &);
    CowString::CharProxy  operator[](std::size_t index );
    const char* c_str() const ;//{ return _pstr;}
    std::size_t size() const;// { return strlen(_pstr); }

    int getRefCount()const {
        return  *(int*)(_pstr - kRefCountLength) ;
    }

    friend ostream& operator<< (ostream & os, const CharProxy &c);
    friend ostream & operator<<(ostream & os , const CowString & rhs);

private:
    void initRefCount();
    
    void increaseRefCount();
     
    void decreaseRefCount();
        

    char * mallocCowString(const char * p = nullptr);
    void  releaseCowString();
private:
    static const int kRefCountLength = 4;  //k 是const 的缩写
    char * _pstr;
};

ostream & operator<<(ostream & os ,const  CowString & rhs);
ostream& operator<< (ostream & os, const CowString::CharProxy &c);


#endif