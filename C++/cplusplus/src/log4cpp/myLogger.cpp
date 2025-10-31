#include"myLogger.h"
#include<iostream>
// #include<string>
//#include<log4cpp/Category.hh>
#include<log4cpp/Priority.hh>
#include<log4cpp/PatternLayout.hh>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/FileAppender.hh>

using std::cout;
using std::endl;
using namespace log4cpp;

Mylogger * Mylogger::_pInstance = nullptr;
Mylogger::Mylogger():_ct(Category::getRoot().getInstance("myct")) {
    auto ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p] %m%n ");
    auto ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d %c [%p] %m%n ");


    auto pos = new OstreamAppender("console" , &cout);
    pos->setLayout(ptn1);

    auto pfile = new FileAppender("fileAppender" , "mylogger.log");
    pos->setLayout(ptn2);

    _ct.setPriority(Priority::DEBUG);
    _ct.addAppender(pos);
    _ct.addAppender(pfile);
}

Mylogger::~Mylogger(){
    Category::shutdown();
    //cout<<" ~Mylooger "<<endl;
}

Mylogger * Mylogger::getInstace(){
    if(nullptr == _pInstance){
        _pInstance = new Mylogger();
    }
    return _pInstance;
}

void Mylogger::destory(){
    if(_pInstance){
        delete _pInstance;
        _pInstance = nullptr;
    }
}

void Mylogger::warn(const char * msg){
    _ct.warn(msg);
}
void Mylogger::error(const char * msg){
    _ct.error(msg);
}
void Mylogger::debug(const char * msg){
    _ct.debug(msg);
}
void Mylogger::info(const char * msg){
    _ct.info(msg);
}

std::string addPrefix1(const char * msg){

	std::string str = std::string("[ ").append(__FILE__)
				.append(" : ").append(__func__)
				.append(" : ").append(std::to_string(__LINE__))
				.append(" ] ").append(msg);
	return str;
}