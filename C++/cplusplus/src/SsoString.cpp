#include<iostream>
#include<cstring>
using std::cout;
using std::endl;
using std::ostream;

class SsoString{
public:
    SsoString(const char * pstr){
        _size = strlen(pstr);
        if(_size <= 15){
            _capacity = 15;
            memset(_buffer._local, 0 , sizeof(_buffer._local));
            strcpy(_buffer._local , pstr);
        }else{
            _capacity = _size;
            _buffer._pointer = new char[_size + 1]();
            strcpy(_buffer._pointer, pstr);
        }
    }
    //有时 初始化列表只适合初始化部分成员 ， 在函数体中完成剩余部分的赋值
    SsoString(const SsoString &rhs):_size(rhs._size), _capacity(rhs._capacity){
        if(_size <=15){
            memset(_buffer._local, 0 , sizeof(_buffer._local));
            strcpy(_buffer._local , rhs._buffer._local);
        }else{
            _buffer._pointer = new char[_size + 1]();
            strcpy(_buffer._pointer, rhs._buffer._pointer);
        }
    }
    ~SsoString(){
        if(_size >15){
            //对于短字符串， _local这块内存存了东西， _pointer 不是空指针，
            delete [] _buffer._pointer;
            _buffer._pointer = nullptr;
        }
    }
    char & operator[](size_t index){ 
        if(index >= _size ){  //比如 “Hello” , index 范围0-4 ， size 是5
            cout <<"out of range "<<endl;
            static char nullchar = '\0';
            return nullchar;
        }
        if(_size > 15){
            return _buffer._pointer[index];
        }else{
            return _buffer._local[index];
        }
    }
    friend ostream & operator<<(ostream & os , const SsoString &rhs);

private:
    union Buffer{
        char * _pointer;
        char _local[16];
    };
    size_t _size;
    size_t _capacity;
    Buffer _buffer;
};
ostream & operator<<(ostream & os , const SsoString &rhs){
    if(rhs._size <= 15){
        os<<rhs._buffer._local;
    }else{
        os<<rhs._buffer._pointer;
    }
    return os;
}

void test(){
    SsoString strl("hello");
    cout << strl << endl;
    cout << &strl << endl;
    printf("%p\n",&strl[0]);
    cout << strl[0]<< endl;
    strl[0]='H';
    cout << strl << endl;
    /*//测试短字符串 */
    cout << endl;
    SsoString str2("hello,world!!!!!");
    cout << str2 << endl;
    cout << &str2 << endl;
    printf("%p\n",&str2[0]);
    cout << str2[0]<< endl;
    str2[0]='X';
    cout << str2 << endl;
    cout << endl;
    SsoString str3 = strl;
    cout << str3 << endl;
    SsoString str4 = str2;
    cout<<str4<<endl<<endl;;

    printf("%p\n",&str3[0]);
    printf("%p\n",&str4[0]);
}
int main(){
    test();
}