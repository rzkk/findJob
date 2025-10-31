#include<iostream>
#include<fstream>
#include<string>
#include<limits>
#include<unistd.h>
using std::cin;
using std::cout;
using std::endl;

namespace StreamStatus{

void printStreamStatus(const std::istream &is){
    cout<<"is cin good "<<is.good()<<endl;
    cout<<"is cin bad "<<is.bad()<<endl;
    cout<<"is cin fail "<<is.fail()<<endl;
    cout<<"is cin eof "<<is.eof()<<endl<<endl;

}
void test(){

    printStreamStatus(cin);

    int num1 = 10 ;

    cin>>num1;
    cout<<"num1 : "<<num1<<endl;
    printStreamStatus(cin);

    if(!cin.good()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string str;
    cin>>str;
    cout<<"str : "<<str<<endl;
    printStreamStatus(cin);

    // std::ifstream ifs;
    // ifs.seekg(20);
}

void test2(){   
    int num ;
    while(cin>>num , !cin.eof()){  // ctrl + D
        if(cin.bad()){
            cout<<"cin has broken "<<endl;
            return ;
        }else if(cin.fail()){  // 可恢复错误
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max() , '\n');
            cout<<"请输入一个 int 数据"<<endl;
        }else{
            cout<<"num : "<<num<<endl;
            break;
        }
    }
}
void test3(){
    for(int i =0;i<1027;++i){
        cout<<'a';
    }
    
    cout<<std::ends;
    sleep(5);
}
}
#include<cstring>
namespace explicit_test{

class CxString
{
private:
    char * _p;
    int _size;
public:
    explicit  CxString(int size);
    explicit CxString(const char * p);
    CxString(const CxString & c);
    ~CxString();
    CxString & operator =(const CxString &c){
        if(this != &c){
            delete  _p;
            _size = strlen(c._p) +1;
            _p = (char *)malloc(_size + 1);
            strcpy(_p , c._p);
        }
        return *this;
    }
};

CxString::CxString(int size)
{
    _size = size;
    _p = (char *)malloc(size + 1);
    memset(_p , 0, size+1);
    cout<<"CxString::CxString(int size)\n";
}
CxString::CxString(const char * p)
{
    _size = strlen(p) +1;
    _p = (char *)malloc(_size + 1);
    strcpy(_p , p);
    cout<<"CxString::CxString(const char * p)\n";
}
CxString::CxString(const CxString & c){
 
    _size = strlen(c._p) +1;
    _p = (char *)malloc(_size + 1);
    strcpy(_p , c._p);
        
}
CxString::~CxString()
{
    if(_p){
        delete  _p;
        _p = nullptr;
    }
}

void test()
{
    CxString string1(24);     // 这样是OK的, 为CxString预分配24字节的大小的内存  
    CxString string2 (10);    // 这样是OK的, 为CxString预分配10字节的大小的内存  
//    //CxString string3;         // 这样是不行的, 因为没有默认构造函数, 错误为: “CxString”: 没有合适的默认构造函数可用  
//     CxString string4("aaaa"); // 这样是OK的  
//     CxString string5 = "bbb"; // 这样也是OK的, 调用的是CxString(const char *p)  
//     CxString string6 = 'c';   // 这样也是OK的, 其实调用的是CxString(int size), 且size等于'c'的ascii码  
//     string1 = 2;              // 这样也是OK的, 为CxString预分配2字节的大小的内存  
//     string2 = 3;              // 这样也是OK的, 为CxString预分配3字节的大小的内存  
    //string2 = string1;        // 这样也是OK的, 至少编译是没问题的, 但是如果析构函数里用free释放_pstr内存指针的时候可能会报错, 完整的代码必须重载运算符"=", 并在其中处理内存释放  
}
}
#include<fstream>
#include<cstring>
#include<sstream>
namespace fstreamTest{
using std::ifstream;
using std::string;
void test1(){
    std::ifstream ifs("test.txt");

    if(!ifs){
        cout<<"open file failed\n";
    }
    std::string str;
    while(ifs>>str){
        cout<<str<<endl;
    }
    ifs.close();
}
void test2(){
    //std::ofstream ofs1("test1.txt"  ,std::ios_base::app);
    //std::ofstream ofs2("test2.txt"  ,std::ios_base::ate);

    ifstream ifs1("test1.txt");

    char buf[100] = {0};

    while(ifs1.getline(buf,sizeof(buf))){
        cout<<buf<<endl;
        memset(buf, 0 , sizeof(buf));
    }
    ifs1.close();
    ifstream ifs2("test2.txt");
    string str;
    while(std::getline(ifs2, str)){
        cout<<str<<endl;
    }
    ifs2.close();

}
void test3(){
    ifstream  ifs("test3.txt" , std::ios_base::ate ); //std::ios_base::in//

    //ifs.seekg(0, std::ios::end);

    long length= ifs.tellg();

    cout<<length<<endl;

    char * pstr = new char[length]();
    ifs.seekg(0);
    ifs.read(pstr, length);

    string str(pstr);
    cout<<str;

    ifs.close();
}
using std::ofstream;

void test4(){
    ofstream ofs1("test1.txt",std::ios::app);

    string line  = "aaaaaaaa\n";

    cin >>line;
    line += '\n';
    ofs1<<line;

    char buf[100] = "qwert";
    ofs1.write(buf,strlen(buf));


    ofs1.close();
}

void test5(){
    string s("123 456");
    int num1 = 0, num2 = 0;

    std::istringstream iss(s);

    iss >>num1 >> num2;
    cout<<num1 <<" "<<num2<<endl;

}
void readConfig(){
    ifstream ifs("my.conf");

    if(!ifs){
        cout<<"open file failed\n";
        return ;
    }
    string line;
    string key , value;
    while(getline(ifs, line)){
        std::istringstream iss(line);
        iss>>key >> value;
        cout<<key<<"  "<<value<<endl;
    }
    

}

void test6(){
    int num1 = 123, num2 = 456;
    float num3 = 789.123;

    std::ostringstream oss;
    oss <<num1 <<" "<<num2<<" "<<num3<<endl;
    cout<<oss.str();

    std::to_string(num1);
}
}

int main(){

    //StreamStatus::test3();
    fstreamTest::test6();
    
    return 0;
}