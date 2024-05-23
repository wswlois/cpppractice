
#include <iostream>
#include "Mylogger1.h"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using namespace log4cpp;
Mylogger * Mylogger::_pInstance = nullptr;
Mylogger::Mylogger()
    :_category(Category::getRoot().getInstance("sales"))
    ,_layout(new PatternLayout())
    ,_oAppender(new OstreamAppender("console",&cout))
    ,_fAppender(new FileAppender("fileApp","wd.log"))
    ,_rFAppender(new RollingFileAppender("rollingfileApp","rollingwd.log",1024,4))
    {

        _layout->setConversionPattern("%d %c [%p] %m%n");
        _oAppender->setLayout(_layout);
        _category.setPriority(Priority::WARN);
        _category.addAppender(_oAppender);


    }
void Mylogger::emerge(const char *msg)
{
    _category.emerg(msg);
}
void Mylogger::fatal(const char *msg)
{
    _category.fatal(msg);
}
void Mylogger::alert(const char *msg)
{
    _category.alert(msg);
}
void Mylogger::crit(const char *msg)
{
    _category.crit(msg);
}
void Mylogger::error(const char *msg)
{
    _category.error(msg);
}
void Mylogger::warn(const char *msg)
{
    _category.warn(msg);
}
void Mylogger::notice(const char *msg)
{
    _category.notice(msg);
}
void Mylogger::info(const char *msg)
{
    _category.info(msg);
}
void Mylogger::debug(const char *msg)
{
    _category.debug(msg);
}
void Mylogger::notset(const char *msg)
{
    //设置错误
    /* _category.notset(msg); */
}

