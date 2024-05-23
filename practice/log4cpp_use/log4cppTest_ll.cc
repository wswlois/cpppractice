#include <iostream>
#include <log4cpp/SimpleLayout.hh>
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
using std::cout;
using std::endl;
using namespace log4cpp;

int main(int argc, char** argv) {
    //1.日志的布局
    SimpleLayout *ps1 = new SimpleLayout();
    //基类指针指向派生类对象的写法
    //OstreamAppender的构造函数第一个参数代表输出目的地名
    //随便写，一般是提示的信息
    //第二个参数是ostream *
	//Appender *appender1 = new OstreamAppender("console", &std::cout);
    //让输出器和格式化器绑定（设置布局）—— 采用了基本布局
	//appender1->setLayout(new BasicLayout());

    //2.日志的目的地
    OstreamAppender *pos = new OstreamAppender("ostream",&cout);
    pos->setLayout(ps1);
    //创建了第二个输出器，让文件作为目的地
    //第一个参数随便写，第二个参数是日志保存的文件名
	//Appender *appender2 = new FileAppender("default", "program.log");
    //让第二个输出器和格式化器绑定（设置布局）—— 采用了基本布局
    //这里使用的是BasicLayout.hh那个的输出，
    //到时候可以把这个头文件删除
    //，然后自己使用新的自己设计的时间从1970年1月1日的
	//appender2->setLayout(new BasicLayout());

    //3.Catagory的种类
    Category &root = Category::getRoot();
    root.addAppender(pos);

    //创建日志记录器
	//Category& root = Category::getRoot();

    //4.过滤器
    root.setPriority(Priority::DEBUG);
    //设置日志过滤器（日志系统的优先级）
    //如果日志的优先级高于或等于系统优先级，才保存日志
	//root.setPriority(Priority::WARN);
    //日志记录器与输出器进行绑定,root的日志输出到终端
	//root.addAppender(appender1);

    //创建了Root下一级的叶子结点（Categor对象sub1）
	//Category& sub1 = Category::getInstance("sub1");
	//sub1.addAppender(appender2);

    //记录日志
    root.fatal("this is an fatal message");
    root.alert("this is an alert message");
    root.error("this is an error message");
    root.warn("this is an warn message");
    root.alert("this is an alert message");
    root.alert("this is an alert message");
    root.alert("this is an alert message");

	// use of functions for logging messages
	//root.error("root error");
	//root.info("root info");
	//sub1.error("sub1 error");
	//sub1.warn("sub1 warn");

	// printf-style for logging variables
	//root.warn("%d + %d == %s ?", 1, 1, "two");

	// use of streams for logging messages
	//root << log4cpp::Priority::ERROR << "Streamed root error";
	//root << log4cpp::Priority::INFO << "Streamed root info";
	//sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
	//sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

	// or this way:
	//root.errorStream() << "Another streamed error";

    //回收内存
    Category::shutdown();
	return 0;
}

