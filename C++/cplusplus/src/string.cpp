#include<string>
#include<vector>
#include<iostream>

using std::string;
using std::cout;
using std::endl;
using std::vector;
void test1()
{
    string str1;  // 空         


    string str2 = "helloworld"; 
    string str3("helloworld");  
    string str4("helloworld",3); //截取前3个
    string str5("helloworld", 1,3);  // 下标1 ， 开始复制3个字符



    const char * cstr = "helloworld";
    string str6 = cstr; 
    string str7(cstr); 
    string str8(cstr, 3); 
    string str9(cstr, 1,3); 
    



    string str10 = str2; 
    string str11(str2); 
    string str12(str2, 3);   // 从下标3 ， 开始往后
    string str13(str2, 1,3); 
    

    cout<<str4<<endl;
    cout<<str8<<endl;
   cout<<str12<<endl;




    //string str10(10, 'a');  //10个a


    //cout<<"str10: \""<<str10<<"\""<<endl;
 
   
    //////迭代器
    // char arr[] = "helloworld";
    // string str11(arr , arr+7);
    // //cout<<"str11: \""<<str11<<"\""<<endl;

    // string::iterator it1 = str11.begin();
    // auto it2 = str11.end();  //自动推导类型

    //string str12(it1 , it2);
}

void test2()
{
    string str1  = "hello";
    string str2  = "world";
    string str3 = str1 + ' '+ str2+ "!";

    cout<<str3<<endl;
}
void test3()
{
    string s1 = "hello";
    string s2 ,s3,s4,s5;
    s2.assign(s1,2);
    s3.assign("hello",2);

    s4.assign("hello ",2,2);

    cout<<s2<<endl;
    cout<<s3<<endl;
    cout<<s4<<endl;
}
void test4()
{
    string s1 = "hello";

    string s2 ,s3,s4,s5,s6,s7;

    s2.append("hello");

    s2.append(s1,2);
    s3.append("hello",2);

    s4.append("hello ",2,2);

    cout<<s2<<endl;
    cout<<s3<<endl;
    cout<<s4<<endl;

    s5.append(s2.begin(),s2.end());
    cout<<s5<<endl;
}
void test5()
{
    string s1 = "aaaaaa";
    string s2 = "llo";
    const char * p = "llo";

    s1.find(p);
    cout<< s1.rfind(p ,3)<<endl;
    //&(s1 + s2);
    if(string::npos == s1.find(p))
    {

    }
    //s1.find(p , 2 , 2);

    // s1.find("llo");
    // s1.find("llo" , 2);
    // s1.find("llo" , 2 , 2);


    // s1.find(s2);
    // s1.find(s2 , 2);
    // //s1.find(s2 , 2 , 2);

     s1.find('d');
     char c = 'd';
     s1.find(c,2);

    
    //s1.insert(1,s2 );
    //s1.insert(1,s2,2 );
    //s1.insert(1,s2,2 ,2);

    //s1.insert(1,"llo" );
    //s1.insert(1,"123456",2 );
    s2 = "123456";
    s1.insert(1,s2,2);
    cout<<s1<<endl;
    //s1.insert(1,"llo",2 ,2);

}
void test6()
{
    string  str = "helloworld";

    for(std::size_t i = 0;i<str.size();++i)
    {
        cout<<str.at(i)<<" ";
    }
    cout<<endl;

    for(auto &c : str)
    {
        cout<<c<<" ";
    }
    cout<<endl;

    string::iterator it = str.begin();
    //auto it2 = str.end();

    for(;it != str.end();++it)
    {
        cout<<*it<<" ";
    }
    cout<<endl;

}


int main()
{

    test6();    


    
}