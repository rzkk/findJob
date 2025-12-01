#include<iostream>

int main(){
    FILE * fp = fopen("file1","r+");
   printf("%p \n",fp->_IO_read_base); 
   printf("%p ",fp->_IO_buf_base); 
    
}