#pragma once

#include<iostream>
#include<string>
 #include<cstring>
#include<vector>
// #include <cassert>
// #include<iostream>
// #include<stdlib.h>
// #include<string.h>
// #include<stdio.h>

#include<sys/stat.h>  // chmod  mkdir
#include<sys/types.h>//mkdir  // opendir closedir readdir 

#include<unistd.h>  // unix std // getcwd
#include<stdlib.h>  // malloc


#include <dirent.h> // opendir closedir readdir 


using std::size_t;
using std::cout;
using std::endl;
using std::string;
using std::vector;

#define ARGS_CHECK(argc, num ) do {  \
    if(argc != num){  \
        fprintf(stderr , "[%s:%s:%d]: args num error \n " ,__FILE__,__func__, __LINE__  ); \
        std::abort();\
    }\
    } while (0)

// —— 退出版：检测到 value == bad 则打印信息并终止 —— //
template <typename T1, typename T2>
inline void errorcheck_eq_die(const T1& value, const T2& bad,
                              const char* message,
                              const char* file,
                              int line, 
                              const char* func)
{
    if (value == bad) {
        std::fprintf(stderr, "[%s:%s:%d] ", file,func, line );
        perror(message);
        std::fflush(stderr);
        std::abort(); 
    }
}



// —— 便捷宏：自动填充文件/行号/函数名 —— 
#define ERROR_CHECK(val, bad, msg) \
    do {  \
        errorcheck_eq_die((val), (bad), (msg), __FILE__, __LINE__, __func__); \
    } while (0)



// template<class T1 , class  T2 >
// // inline

// void errorcheck(const T1 &t1 , const T2& t2, const char* message ){ //, const char message[]
//     if(t1 ==t2){
//         perror(message);//message.c_str()
//         assert(0);
//     }
  
// }


void add();
