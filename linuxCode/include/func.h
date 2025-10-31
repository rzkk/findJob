#ifndef __FUNC_H__
#define __FUNC_H__

#include<iostream>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h> 

#include<sys/types.h> 
#include<dirent.h> 
#include <grp.h>
#include <pwd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include<sys/time.h>


#include <pthread.h>


 #include <arpa/inet.h>

 #include <netdb.h>
 #include <sys/socket.h> 

  #include <sys/epoll.h>

    #include <sys/sendfile.h>
using std::size_t;
using std::cout;
using std::endl;

void  errorEqualCheck(int argc , int num,const char *errormsg);

void errorEqualCheck(void * argc1 , void * argc2,const char *errormsg);


void errorUnequalCheck(void * argc1 , void * argc2,const char *errormsg);

void  errorUnequalCheck(int argc , int num,const char *errormsg);

void  argsCheck(int argc , int num);

#endif