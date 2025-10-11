#ifndef _MYLOGGER_
#define _MYLOGGER_

#include<log4cpp/Category.hh>
#include<string>

#define addPrefix(msg) std::string("[ ").append(__FILE__) \
				        .append(" : ").append(__func__) \
				        .append(" : ").append(std::to_string(__LINE__)) \
				        .append(" ] ").append(msg) //直接替换之后 在编译阶段进行检查
#define LogDebug(msg)  \
	Mylogger::getInstace()->debug(addPrefix(msg).c_str());

class Mylogger{
public:
   
	void warn(const char * msg);
	void error(const char * msg);
	void debug(const char * msg);
	void info(const char * msg);

    static Mylogger* getInstace();
    static void destory();


private: 
    Mylogger();
   ~Mylogger();
	log4cpp::Category & _ct;
	static Mylogger * _pInstance;
};
std::string addPrefix1(const char * msg);

#endif