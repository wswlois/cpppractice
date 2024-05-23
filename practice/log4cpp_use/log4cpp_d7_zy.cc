#include <iostream>
#include "log4cpp/OstreamAppender.hh"
#include <log4cpp/PatternLayout.hh>
#include "log4cpp/Category.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/RollingFileAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
using std::cout;
using std::endl;
using std::ofstream;
using namespace log4cpp;

int main(int argc, char** argv) {
    //1.设置日志的布局(格式化器)
    PatternLayout *ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d %c [%p] %m%n");

    PatternLayout *ptn3 = new PatternLayout();
    ptn3->setConversionPattern("%d %c [%p] %m%n");

    //2.创建日志的目的地对象
    OstreamAppender *appender1 = new OstreamAppender("console",&cout);
    appender1->setLayout(ptn1);

    FileAppender * appender2 = new FileAppender("fileApp","d7.log");
    appender2->setLayout(ptn2);

    //10K,5卷
    RollingFileAppender *appender3 = new RollingFileAppender("rollingfileApp","rollingd7.log",10*1024,4);
    appender3->setLayout(ptn3);

    //3.Catagory的种类(创建日志记录器)(核心)(日志来源)
    /* Category &d7log = Category::getInstance("d7log"); */
    //老师，这个我还是没搞懂getRoot()什么时候加什么时候不加
    Category &d7log = Category::getRoot().getInstance("d7log");
    //3.1过滤器（设置日志系统优先级）
    d7log.setPriority(Priority::WARN);
    //3.2设置日志目的地绑定(日志记录器和输出器进行绑定)(终端、文件、回卷文件)
    d7log.addAppender(appender1);
    d7log.addAppender(appender2);
    d7log.addAppender(appender3);


    //创建了Root下一级的叶子结点（Categor对象sub1）
	//Category& sub1 = Category::getInstance("sub1");
	//sub1.addAppender(appender2);
    //如果想再创建sub1的子节点sub11就是
	//Category& sub11 = Category::getInstance("sub1.sub11");
    //前面的sub1表示的是下面过滤设置的
    //后面的sub1表示的是错误消息中前面显示sub1
	//Category& sub1 = Category::getInstance("sub1");
	//sub1.addAppender(pos);
    //让子节点独立生成记录信息，不再继承父节点
    //sub1.setAppender(appender2);
    //sub1.setAdditivity(false);//不再从父节点继承appender
    //5.记录日志
    int count = 40;
    while(count-->0)
    {

    d7log.emerg("this is an emerge message");
    d7log.fatal("this is an fatal message");
    d7log.alert("this is an alert message");
    d7log.crit("this is an crit message");
    d7log.error("this is an error message");
    d7log.warn("this is an warn message");
    d7log.notice("this is an notice message");
    d7log.info("this is an info message");
    }

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

