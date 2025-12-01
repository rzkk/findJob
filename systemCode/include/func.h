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

#include <pwd.h>
#include <grp.h>

#include <fcntl.h>
#include <sys/mman.h>

#include<sys/wait.h>

#include <syslog.h>

#include<sys/ipc.h>  // shmget 
#include<sys/shm.h>


#include<signal.h>

#include<sys/time.h>
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


inline void errorcheak_pthread(int ret ,  const char* message,const char* file,int line, const char* func){
     if(ret != 0){  
        fprintf(stderr , "[%s:%s:%d]%s:%s \n" ,file,func, line ,message , strerror(ret) ); 
        //perror(message); 
        //strerror(ret);
        std::fflush(stderr); 
        std::abort();
    }
}


#define THREAD_ERROR_CHECK(ret, msg )\
    do {  \
        errorcheak_pthread((ret) ,(msg)  ,  __FILE__, __LINE__, __func__) ; \
    } while (0)


void add();
