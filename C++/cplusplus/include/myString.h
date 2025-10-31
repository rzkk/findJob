/*
 * @Author: rzk ruanzk2098@gmial.com
 * @Date: 2024-12-08 19:33:14
 * @LastEditors: rzk ruanzk2098@gmial.com
 * @LastEditTime: 2024-12-08 22:20:07
 * @FilePath: /src/home/rzk/documents/learning/cplusplus/include/myString.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#ifndef _MYSTRING_H_
#define _MYSTRING_H_


#include<iostream>
class String{
public:
    String();
    String(const char * );
    String(const String &);
    String( String &&);
    ~String();

    String & operator=(const String&);
    String & operator=( String&&);
    String & operator=(const char *);

    String & operator+=(const String&);
    String & operator+=(const char *);

    char &operator[](size_t index);
    const char &operator[](size_t index) const;

    size_t size() const ;
    const char* c_str() const;

    friend bool operator==(const String &,const String &);
    friend bool operator!=(const String &,const String &);
    friend bool operator<(const String &,const String &);
    friend bool operator>(const String &,const String &);
    friend bool operator<=(const String &,const String &);
    friend bool operator>=(const String &,const String &);
    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    char *_pstr;
    size_t _size;
};

bool operator==(const String &,const String &);
bool operator!=(const String &,const String &);
bool operator<(const String &,const String &);
bool operator>(const String &,const String &);
bool operator<=(const String &,const String &);
bool operator>=(const String &,const String &);
std::ostream &operator<<(std::ostream &os, const String &s);
std::istream &operator>>(std::istream &is, String &s);

#endif
