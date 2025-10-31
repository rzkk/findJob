#include"func.h"


#if 1   // chmod  

#endif 

namespace fileTestNS{
void test1(int argc , char * argv[]){
    ARGS_CHECK( argc , 2);
    FILE* fp = fopen(argv[1] ,"r+" );
#ifdef DEBUG
    ERROR_CHECK(fp ,nullptr , "fopen");// 若 fp == nullptr 报错
#endif
    char buf1[1024] = {0};
    int ret = 0;
    cout<<sizeof(buf1)<<endl;

    ret = fread(buf1 , 1, sizeof(buf1), fp);
    cout<<ret<<endl;
    cout<<"buf1 : "<<buf1<<endl;

    FILE* fp2 = fopen(argv[1] ,"r+" );
    char buf2[1024] = {0};
    ret = fread(buf2 , 12, 1, fp2);
    cout<<ret<<endl;
    cout<<buf2<<endl;
    //cout<<buf<<endl;
    //cout<<strlen(buf)<<endl;
    //return 0;
} 
};
namespace chmodNS{
void test(int argc , char * argv[]){
    ARGS_CHECK(argc , 2);
    int ret = chmod(argv[1] , 0777); //0777 八进制  // 0x777  十六进制
    ERROR_CHECK(ret , -1, "chmod");
 }
};
namespace getcwdNS{
void test1(){
    char path[1024] = {0};
    char * ret = getcwd(path , sizeof(path)); 
    ERROR_CHECK(ret , nullptr, "getcwd ");
    cout<<path<<endl;
 }
void test2(){

    char path[12] = {0};
    char * ret = getcwd(path , sizeof(path)); 
    ERROR_CHECK(ret , nullptr, "getcwd ");
    cout<<path<<endl;
 }
void test3(){
    char * path = (char*)malloc(1024);
    char * ret = getcwd(path , sizeof(path)); 
    ERROR_CHECK(ret , nullptr, "getcwd ");
    cout<<path<<endl;
}
};


namespace chdirNS{
void test(int argc , char * argv[]){
    ARGS_CHECK(argc,2);
 
    //获取当前工作目录
    cout<<getcwd(NULL ,0)<<endl;

    //改目录
    int  ret2 = chdir(argv[1]); 
    ERROR_CHECK(ret2 , -1, "getcwd ");
    
    //获取当前工作目录
        
    cout<<getcwd(NULL ,0)<<endl;
 
 }
};

namespace mkdirNS{
void test(int argc , char * argv[]){
    ARGS_CHECK(argc , 2);

    int ret = mkdir(argv[1] ,0777 );
    ERROR_CHECK(ret , -1 , "mkdir");

}
};

namespace directoryNS{
void test1(int argc , char * argv[]){
    ARGS_CHECK(argc , 2);
    DIR * dirp = opendir(argv[1]);
    ERROR_CHECK(dirp , nullptr , "opendir");

    struct dirent * pdirent;

    while( ( pdirent = readdir(dirp) )  != NULL){
        printf("%ld %d %d  %s \n",  pdirent->d_ino,   
                                pdirent->d_reclen,   //与文件名有关
                                pdirent->d_type,
                                pdirent->d_name);
    }
    cout<<DT_DIR<<" "<<DT_REG<<endl;
    closedir(dirp);
}

void test2(int argc , char * argv[]){
    ARGS_CHECK(argc , 2);
    DIR * dirp = opendir(argv[1]);
    ERROR_CHECK(dirp , nullptr , "opendir");

    struct dirent * pdirent;
    long loc = 0;
    while( ( pdirent = readdir(dirp) )  != NULL){
        printf("%ld %d %d  %s \n",  pdirent->d_ino,   
                                pdirent->d_reclen,   //与文件名有关
                                pdirent->d_type,
                                pdirent->d_name);
        if( strcmp( "dir2" ,  pdirent ->d_name ) == 0){  // C的字符串比较
            loc = telldir(dirp);
        }
    }
    printf("---------------------\n");
    seekdir(dirp , loc);   //回到dir2
    pdirent = readdir(dirp);
    printf("%ld %d %d  %s \n",  pdirent->d_ino,   
                                pdirent->d_reclen,   //与文件名有关
                                pdirent->d_type,
                                pdirent->d_name);
     
    closedir(dirp);
}
void test3(int argc , char * argv[]){
    ARGS_CHECK(argc , 2);
    DIR * dirp = opendir(argv[1]);
    ERROR_CHECK(dirp , nullptr , "opendir");

    struct dirent * pdirent;
    //long loc = 0;
    while( ( pdirent = readdir(dirp) )  != NULL){
        printf("%ld %d %d  %s \n",  pdirent->d_ino,   
                                pdirent->d_reclen,   //与文件名有关
                                pdirent->d_type,
                                pdirent->d_name);
      
    }
    printf("---------------------\n");
    rewinddir(dirp);   //回到dir2
    pdirent = readdir(dirp);
    printf("%ld %d %d  %s \n",  pdirent->d_ino,   
                                pdirent->d_reclen,   //与文件名有关
                                pdirent->d_type,
                                pdirent->d_name);
     
    closedir(dirp);
}
void test4(int argc , char * argv[]){
    ARGS_CHECK(argc , 2);
    DIR * dirp = opendir(argv[1]);
    ERROR_CHECK(dirp , nullptr , "opendir");

    struct dirent * pdirent;
   
    while( ( pdirent = readdir(dirp) )  != NULL){
        //文件名 -》 路径
        char path[1024] = {0};
        sprintf(path , "%s%s%s" , argv[1] , "/" , pdirent->d_name);
        
        struct stat statbuf;
        int ret = stat(path , & statbuf);
        ERROR_CHECK(ret , -1 ,"stat");
        
        printf("%o %ld %d %d %ld %s %s\n" , statbuf.st_mode,
                                            statbuf.st_nlink, 
                                        statbuf.st_uid   ,
                                    statbuf.st_gid,
                                statbuf.st_size,
                           ctime( &statbuf.st_mtime),
                        pdirent->d_name );

    }
    closedir(dirp);
}

char mon[12][4] = { "Jan" , "Feb" , "Mar" , "Apr" , "May" ,"Jun" , "Jul" ,"Aug" , "Sep" , "Oct" ,"Nov" , "Dec"};
char modeType[8][4] = { "---" , "--x" , "-w-" , "-rw" ,"r--", "r-x" ,"rw-" , "rwx"};

void  modeTostring(struct stat & st , char* modeStr){ // modeStr 长度 11 
    
    switch (st.st_mode & S_IFMT) {
            //case S_IFBLK:  printf("block device\n");            break;
            //case S_IFCHR:  printf("character device\n");        break;
            case S_IFDIR:  
                    modeStr[0] = 'd';//printf("directory\n");               
                    break;
            //case S_IFIFO:  printf("FIFO/pipe\n");               break;
            case S_IFLNK:  
                     modeStr[0]  = 'l';//printf("symlink\n");                 
                    break;
            case S_IFREG:  
                modeStr[0] = '-';//printf("regular file\n");            
                break;
            //case S_IFSOCK: printf("socket\n");                  break;
            default:       modeStr[0] = '?';                break;
    }
    unsigned int mask = 07;
    unsigned int stMode = st.st_mode;
    for(int i = 2 ;i>= 0;i--){

       char * temp = modeType[stMode & mask ];
     
       modeStr[i * 3 +1 ] = temp[0];
       modeStr[i * 3 +2]  = temp[1]; 
       modeStr[i * 3 +3]  = temp[2];
       stMode = stMode>>3;
    }
} 

void myls(int argc , char * argv[]){
    ARGS_CHECK(argc ,2);
    DIR * pdir = opendir(argv[1]);
    ERROR_CHECK(pdir , nullptr , "opendir");

    struct dirent * pdirent;
    chdir(argv[1]);  //切换当前目录到 要开的文件夹
    while(( pdirent = readdir(pdir)) != nullptr){
        //char path[1024] = {0};
        //sprintf(path , "%s%s%s" , argv[1] , "/", pdirent->d_name);
        struct stat statbuf;
        int ret = stat(pdirent->d_name , &statbuf); 
        ERROR_CHECK(-1, ret , "stat");
       

        char  modeStr[15] = {0};
    
        modeTostring(statbuf , modeStr);

        struct tm *ptime = localtime( & statbuf.st_mtime);

        printf("%s %3ld %4s %4s %5ld %s %02d %02d:%02d %s\n",
            modeStr ,
            statbuf.st_nlink, 
            getpwuid(statbuf.st_uid)->pw_name,
            getgrgid(statbuf.st_gid)->gr_name, 

            statbuf.st_size,

            mon[ptime->tm_mon] , 
            ptime->tm_mday,
            ptime->tm_hour,
            ptime->tm_min,
            pdirent->d_name
         );
    }
    closedir(pdir);
} 

void DFStree(char * dirpath , int depth ){

    DIR * pdir = opendir(dirpath);  
    ERROR_CHECK(pdir , nullptr , "opendir");
    struct dirent * pdirent;
    
    while(( pdirent = readdir(pdir)) != nullptr){ 
        
        if(strcmp( pdirent->d_name , ".") == 0 || strcmp( pdirent->d_name , "..") == 0 )
            continue;
        for(int i = 0 ; i< depth;++i){
            printf("-");
        }
        printf(" %s\n" , pdirent->d_name); 
        if(pdirent->d_type == DT_DIR){
            char path[1024] = {0};
            sprintf(path , "%s%s%s" , dirpath, "/", pdirent->d_name);
            DFStree(path , depth +6 );
        }
 
    }
    //printf("")
    closedir(pdir);
}
void mytree(int argc , char * argv[]){
    ARGS_CHECK(argc ,2);
    //chdir(argv[1]);
    printf("%s\n" , argv[1]);
    DFStree(argv[1] , 6);
}
};

namespace noBufferFileNS{
void test1(int argc , char * argv[]){ // 读磁盘文件
    ARGS_CHECK(argc , 2 );
    int fd = open(argv[1] , O_RDONLY);
    ERROR_CHECK(fd, -1 , "opne");

    char buf[1024] = {0};
    ssize_t ret = 0;
    long sizeCount = 0;
    while( (ret = read(fd , buf , sizeof(buf)) ) != 0 ){
        ERROR_CHECK(ret , -1 , "read");
        sizeCount += ret;
 
        printf("%s",   buf);
        bzero(buf , sizeof(buf));
    }

    cout<<"总计： " << sizeCount<<endl;

    close(fd);
}
void test2(){  // 读设备文件
    char buf[1024] = {0};
    ssize_t ret = read(0 , buf , sizeof(buf));
    ERROR_CHECK(ret , -1 , "read" );
    printf(" %ld  %s " , ret , buf);
}
void test3(int argc , char * argv[]){ //写文本
    ARGS_CHECK(argc , 2);

    int fd = open(argv[1] , O_RDWR | O_CREAT | O_TRUNC , 0666);

    char buf[1024] = "10000";
    ssize_t ret = write(fd , buf , sizeof(buf));
    ERROR_CHECK(ret , -1 , "write" );

    close(fd);
    //printf(" %ld  %s " , ret , buf);
}
void test4(int argc , char * argv[]){ //写 二进制数据
    ARGS_CHECK(argc , 2);

    int fd = open(argv[1] , O_RDWR | O_CREAT | O_TRUNC , 0666);

    int a = 10000;
    ssize_t ret = write(fd , &a , sizeof(a));
    ERROR_CHECK(ret , -1 , "write" );

    int b = 0;
    ret = read(fd, &b , sizeof(b));
    ERROR_CHECK(ret , -1 , "write" );
    cout<<ret<<endl;
    printf("%d \n", b);
    close(fd);
    //printf(" %ld  %s " , ret , buf);
}
void compareFile(char * path1  , char* path2){

    int fd1 = open(path1 , O_RDWR);ERROR_CHECK(fd1 , -1 , "open");
    int fd2 = open(path2, O_RDWR );ERROR_CHECK(fd2 , -1 , "open");

    char buf1[4096] = {0};
    char buf2[4096] = {0};
    ssize_t ret1 ;  ssize_t ret2 ; 
    
    while(1){
        ret1 = read(fd1, buf1 , sizeof(buf1)); 
        ERROR_CHECK(ret1 , -1 , "read");
        ret2 = read(fd2, buf2 , sizeof(buf2));
        ERROR_CHECK(ret2, -1 , "read");

        if(ret1 != ret2){
            printf("长度不一样\n");
            return ;
        } 
        if(ret1 == 0) break;
        if(memcmp(buf1 , buf2 , ret1) != 0 ){
            printf("内容不一样\n");
             return ;
        } 

        bzero(buf1, sizeof(buf1));
        bzero(buf2, sizeof(buf2));
    }
    printf("内容一致\n");
    return ;

}
void mycopy(int argc , char * argv[]){ //./fileTest src desc 
    ARGS_CHECK(argc , 3);
    int fdsrc  = open(argv[1] ,  O_RDWR);ERROR_CHECK(fdsrc , -1 , "open");
    int fddesc = open(argv[2] , O_RDWR | O_CREAT | O_TRUNC , 0666);
    ERROR_CHECK(fddesc , -1 , "open");
    char buf[4096] = {0};
    ssize_t rret ;
    while((rret = read(fdsrc , buf , sizeof(buf))) != 0 ){
        ERROR_CHECK(rret , -1, "read");
        ssize_t wret =  write(fddesc , buf , rret);
        ERROR_CHECK(wret , -1 , "write");
        bzero(buf, sizeof(buf));
    }
    close(fddesc);
    close(fdsrc);
    compareFile(argv[1] , argv[2]) ;
}

void test5(int argc , char * argv[]){  // ftruncate 
    ARGS_CHECK(argc , 2);
    int fd = open(argv[1] , O_RDWR);
    ERROR_CHECK(fd , -1 , "open");

    int ret = ftruncate(fd , 40960);
    ERROR_CHECK(ret , -1 ,"ftruncate");

    close(fd);
}
void test6(int argc , char * argv[]){  // mmap
    ARGS_CHECK(argc , 2);
    int fd = open(argv[1] , O_RDWR);
    ERROR_CHECK( fd, -1 ,"open" );

    //int ret = ftruncate(fd , 5);
    //ERROR_CHECK(ret, -1 ,"ftruncate");

    char * p = (char*)mmap(NULL , 5000, PROT_READ | PROT_WRITE , MAP_SHARED, fd , 0);
    ERROR_CHECK( p , MAP_FAILED , "mmap");

    for(int i = 0 ;i< 10;i++){
        cout<<p[i]<<" ";
    }
    cout<<endl;

     p[9] = 'F';
    //p[4097] = 'F';
    //  for(int i = 0 ;i< 10;i++){
    //     cout<<p[i]<<" ";
    // }
    cout<<endl;
    munmap(p,5000);
    close(fd);
};

void test7(int argc , char * argv[]){ // 文件对象  文件流
    ARGS_CHECK(argc , 2);
    FILE * fp = fopen(argv[1] , "r+");
    ERROR_CHECK(fp , nullptr, "fopon");

    ssize_t ret = write(3 , "hello", 5);
    ret = write(fp->_fileno , "world" , 5);
    ret = write(fileno(fp) , "22222" , 5);
    ERROR_CHECK(ret , -1 , "write");
    fclose(fp);
}
void test8(int argc , char * argv[]){ 
    ARGS_CHECK(argc , 2);
    printf("see me\n");
    close(STDOUT_FILENO);

    int fd = open(argv[1] , O_RDWR);

    cout<<fd<<endl;

    printf("cishi 输出到哪了 \n");

    close(fd);
}

void test9(int argc , char * argv[]){  // dup 
    ARGS_CHECK(argc , 2);
  
    int oldfd = open(argv[1] , O_RDWR | O_CREAT | O_TRUNC);

    int newfd = dup(oldfd);

    cout<<oldfd <<" " <<newfd<<endl;

    
    write(oldfd ,"hello" , 5 );

    write(newfd ,"world" , 5 );
    
   

    close(oldfd);

    write(newfd ,"nihao" , 5 );
    
}
void test10(int argc , char * argv[]){  // dup  + 重定向
    ARGS_CHECK(argc , 2);
    //printf("seeuyuy me\n");
    int fd1 = open(argv[1] , O_RDWR | O_CREAT | O_TRUNC);
   
    ERROR_CHECK(fd1 , -1 , "open");

    dup2(STDOUT_FILENO , 10 );
    close(STDOUT_FILENO);  // 使得描述符 1 空出来了

    int fd2 = dup(fd1); //找到最小的 ，  分配了 1 
    
    cout<<fd2<<endl;;
    printf("nihao\n");
    printf("world\n");
    dup2(10 , 1 );
    //fflush(stdout);
    printf("wwwwww");

    close(fd1);
    close(STDOUT_FILENO);
}
typedef struct{
    int num;
    char name[20];
    int core ; 
    
} Student;

void readstudent(int argc , char * argv[]){
    ARGS_CHECK(argc , 2);
    int fd = open(argv[1] , O_RDWR);
    ERROR_CHECK(fd ,-1 , "open");

    Student stu[3] = { {1 , "zzzz" , 60 } , {2 , "qqq" , 40} , {3,"aaa" , 70}};

    ssize_t ret = 0;
    write(fd , stu , sizeof(stu));
    ERROR_CHECK(ret , -1  , " write");

    lseek(fd , 0 , SEEK_SET);

    Student st;
   
    while( (ret = read(fd , & st , sizeof(st))) != 0){
        ERROR_CHECK(ret , -1  , " read");
        cout<<st.num<<" "<<st.name<<" "<<st.core<<endl;
    }
    close(fd);
}
}

int main(int argc , char * argv[]){
    noBufferFileNS::readstudent(argc , argv);
    //getcwdNS::test3();
    return 0;
}