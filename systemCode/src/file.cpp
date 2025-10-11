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
void test(int argc , char * argv[]){
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

string   longTotime(time_t & mtime){
    struct tm *ptime = localtime(&mtime);
 
    char buf[1024] = {0} ;
    string stime = mon[ptime->tm_mon];
    string day;
    if(ptime->tm_mday / 10 == 0){
        stime  =stime +  "  "+ std::to_string(ptime->tm_mday);
    }else{
        stime  =stime +  " "+ std::to_string(ptime->tm_mday);
    }

    if(ptime->tm_hour / 10 == 0){
        stime  =stime +  " 0"+ std::to_string(ptime->tm_hour);//_01
    }else{
        stime  =stime +  " "+ std::to_string(ptime->tm_hour); //_11
    }
    if(ptime->tm_min / 10 == 0){
        stime  =stime +  ":0"+ std::to_string(ptime->tm_min);
    }else{
        stime  =stime +  ":"+ std::to_string(ptime->tm_min);
    }
    // stime =stime + " "+  std::to_string(ptime->tm_mday) + " "+ std::to_string(ptime->tm_hour)
    //         + ":"+std::to_string(ptime->tm_min) ;
    return stime;
}
void myls(int argc , char * argv[]){
    ARGS_CHECK(argc ,2);
    DIR * pdir = opendir(argv[1]);
    ERROR_CHECK(pdir , nullptr , "opendir");


    struct dirent * pdirent;
    while(( pdirent = readdir(pdir)) != nullptr){
        char path[1024] = {0};
        sprintf(path , "%s%s%s" , argv[1] , "/", pdirent->d_name);
        struct stat statbuf;
        int ret = stat(path , &statbuf); 
        ERROR_CHECK(-1, ret , "stat");
      
        string stime = longTotime(statbuf.st_mtime );
        string name = pdirent->d_name;
        cout<<stime <<" "<<name<<endl;
    }
    
    closedir(pdir);
} 
};



int main(int argc , char * argv[]){
    directoryNS::myls(argc,argv);
    //getcwdNS::test3();
    return 0;
}