#include "func.h"

void  errorEqualCheck(int argc , int num,const char *errormsg){
    if(argc == num)
    {
        perror(errormsg);
        assert(0);
    }
   
}
void errorEqualCheck(void * argc1 , void * argc2,const char *errormsg){
    if(argc1 == argc2)
    {
        perror(errormsg);
        assert(0);
       
    }
}

void errorUnequalCheck(void * argc1 , void * argc2,const char *errormsg){
    if(argc1 != argc2)
    {
        perror(errormsg);
        assert(0);
       
    }
}
void  errorUnequalCheck(int argc , int num,const char *errormsg){
    if(argc != num)
    {
        perror(errormsg);
        assert(0);
    }
   
}
void  argsCheck(int argc , int num){
    if(argc != num)
    {
        fprintf(stderr,"args error!\n");
        assert(0);
    }
 
}