#include<iostream>
#include<mysql/mysql.h>

using std::cout;

















int main(){

    MYSQL *mysql = mysql_init(NULL);
    //localhost : 本机
    //IP ： 可以连接远程的mysql 
    //root: 登录mysql 的用户名
    //qwer : 登录mysql 的密码 => 密码作为命令行参数 or 数据库密码统一
    //test01 :database的名字 
    // 0 : 自动选择端口号
    // NULL: unix_socket 自动选择
    //0: clientflag , usually 0
    MYSQL * cret =  mysql_real_connect(mysql ,"localhost" , "root","qwer","test01" ,0 , NULL , 0);
    //获取报错信息
    if(cret == NULL){
        fprintf(stderr , "mysql_real_connet : %s \n", mysql_error(mysql)  );  
        return -1;
    }

    char name[] = "baijingting";
    char product[] = "shangchunshan";

    char sql[4096] = {0};
    sprintf(sql, "insert into star2 (name ,product) values('%s','%s' );",name ,product);
    cout<<sql<<std::endl;
    //return 0 : 正确 ，非0: 错误
    //int qret = mysql_query(mysql,sql); //执行sql 语句
    // if(qret != 0){
    //     fprintf(stderr , "mysql_query : %s \n", mysql_error(mysql)  );  
    //     return -1;
    // }

    sprintf(sql, "select * from star2;");
    cout<<sql<<std::endl;
    int qret = mysql_query(mysql,sql); //执行sql 语句
    if(qret != 0){
        fprintf(stderr , "mysql_query : %s \n", mysql_error(mysql)  );  
        return -1;
    }

    MYSQL_RES *res = mysql_store_result(mysql); // 把rows 存起来
    printf("rows = %lu ,  col = %d \n" , mysql_num_rows(res) , mysql_num_fields(res));

    MYSQL_ROW row;//每一行 ， 字符串数组
    while( (row = mysql_fetch_row(res)) != NULL){
        for(unsigned int i =0;i< mysql_num_fields(res);++i){
            printf("%s\t",row[i]);
        }
        printf("\n");
    }

    mysql_close(mysql);

    return 0;
}


















