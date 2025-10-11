/*
 * @Author: rzk ruanzk2098@gmial.com
 * @Date: 2024-11-22 20:44:01
 * @LastEditors: rzk ruanzk2098@gmial.com
 * @LastEditTime: 2024-12-04 15:52:05
 * @FilePath: /cplusplus/src/log4cpp/log4cppTest.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// main.cpp

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/RollingFileAppender.hh"
#include "log4cpp/PropertyConfigurator.hh"
#include <fstream>
#include <cstring>

#include<vector>
//using namespace std;
//log4cpp 命名空间


int test(int argc, char** argv) {

	//log4cpp::PropertyConfigurator::configure()

	log4cpp::PatternLayout* patternLayout1 = new  log4cpp::PatternLayout();
	//时间 模块名 优先级 消息本身 换行符
	patternLayout1->setConversionPattern("%d %c [%p] %m  %n"); 
	log4cpp::PatternLayout* patternLayout2 = new  log4cpp::PatternLayout();
	patternLayout2->setConversionPattern("%d %c [%p] %m  %n"); 
	log4cpp::PatternLayout* patternLayout3 = new  log4cpp::PatternLayout();
	patternLayout3->setConversionPattern("%d %c [%p] %m  %n"); 

	//Appender 代表输出器 ， 决定日志的目的地
	//父类指针 指向 子类对象
	//OstreamAppender 第一个参数目的地的描述 ， 随便取
	// 第二个参数 ostream* 决定目的地， &cout代表终端  // ofstream 对象也可以
	log4cpp::Appender *appender1 = 
			new log4cpp::OstreamAppender("console", &std::cout);
	//基类指针指向派生类 ， 基本布局信息
	//目的地与日志格式进行绑定
	//appender1->setLayout( new log4cpp::BasicLayout() );  
	//这里如果想使用自定义的patternLayout ，必须从新定义一个
	//layout 对象与Appender对象 必须一对一
	appender1->setLayout(patternLayout1);


	log4cpp::Appender *appender2 = 
			new log4cpp::FileAppender("default", "program.log");
	//appender2->setLayout(new log4cpp::BasicLayout());
	appender2->setLayout(patternLayout2);

	std::ofstream ofs("program2.log", std::ios::app);//app , 追加格式 
	log4cpp::Appender * appender3 = new log4cpp::OstreamAppender("file" , &ofs);
	appender3->setLayout(new log4cpp::BasicLayout());


	log4cpp::Appender* appender4 
					= new log4cpp::RollingFileAppender(
							"rolling file", 
							"rollingwd.log", 5*1024,
							9);
	appender4->setLayout(patternLayout3);
	
	//getRoot 静态函数
	//Category 单例
	//getRoot 创建root级别的 category 对象（记录器对象）
	log4cpp::Category& root = log4cpp::Category::getRoot();
	//root设置优先级（日志系统优先级，理解为 门槛） 
	root.setPriority(log4cpp::Priority::WARN);
  	// 设置目的地为终端
	root.addAppender(appender1);
	root.addAppender(appender4);

	//getInstance 静态函数
	//sub1 变量名字
	//"sub1" ,日志记录下来的
	//getInstace 创建一个名为sub1 的叶子级别的category 对象
	//sub1继承root的优先级与目的地
	log4cpp::Category& sub1 = log4cpp::Category::getInstance(std::string("sub1"));
	sub1.setPriority(log4cpp::Priority::INFO);// 可以重新设置优先级
	//sub1在输出终端基础上 ， 又添加了一个目的地
	//sub1.addAppender(appender2); 

	//创建subsequence1 同一级的
	log4cpp::Category& sub2 = log4cpp::Category::getInstance(std::string("sub2"));
	//重新设置目的地
	sub2.setAppender(appender3); //setAppender 与addAppender 作用完全一样
	sub2.setAdditivity(false);//Set the additivity flag for this Category instance.
	
	//创建subsequence1 下一级的
	log4cpp::Category& sub11 = log4cpp::Category::getInstance(std::string("sub1.sub11"));


	int count =1000;
	while(count --){
		
		sub2.error("ofstream ");
		sub11.info("sub11 info msg ");

		// use of functions for logging messages
		root.error("root error");// 决定日志信息内容 , 优先级为ERROR
		root.info("root info");  //pass 
		sub1.error("sub1 error"); // 即输出到终端 ， 又保存到文件
		sub1.warn("sub1 warn");  //不会被过滤

		// printf-style for logging variables
		root.warn("%d + %d == %s ?", 1, 1, "two");   //终端

		// use of streams for logging messages
		root << log4cpp::Priority::ERROR << "Streamed root error";
		root << log4cpp::Priority::INFO << "Streamed root info";
		sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
		sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

		// or this way:
		root.errorStream() << "Another streamed error";

		
	}
	
	log4cpp::Category::shutdown(); 
	return 0;
}

#include "myLogger.h"
// #include<string>
namespace instanceLog4cpp{
void test(){
	Mylogger::getInstace()->debug("this log is debug message");
	Mylogger::getInstace()->debug(addPrefix("this log is debug message").c_str());
	LogDebug("this log is debug message");
	//LogDebug(1);
	//std::cout<<addPrefix1("this is a message log \n"); 
	//如果是函数的话 ，__FILE__ 等宏的内容就是这个定义函数addPrefix的了， 不是test
	//宏定义替换是在预处理阶段， 只是替换展开 ， 所以函数里面的__LINE__是69行
	// 
	Mylogger::destory();

}
void test1(){
	std::cout<<__FILE__<<std::endl;
	std::cout<<__func__<<std::endl;
	std::cout<<__LINE__<<std::endl;
}


void test2(){
	
}
}

int main()
{
 	instanceLog4cpp::test();

	return 0;
}