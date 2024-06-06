#ifndef __MYLOGGER_HH__
#define __MYLOGGER_HH__
#include <iostream>                                 
#include <cstring>
#include <string>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Layout.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <stdlib.h>

using std::cout;
using std::string;
#define addPrefix(msg) string("[").append(__FILE__)  \
        .append(":").append(__func__).               \
        append(":").append(std::to_string(__LINE__)) \
        .append("]").append(msg).c_str()

#define LogEmerge(msg) Mylogger::getInstance()->emerge(addPrefix(msg))
#define LogFatal(msg)  Mylogger::getInstance()->fatal(addPrefix(msg))
#define LogAlert(msg) Mylogger::getInstance()->alert(addPrefix(msg))
#define LogCrit(msg) Mylogger::getInstance()->crit(addPrefix(msg))
#define LogError(msg) Mylogger::getInstance()->error(addPrefix(msg))
#define LogWarn(msg) Mylogger::getInstance()->warn(addPrefix(msg))
#define LogNotice(msg) Mylogger::getInstance()->notice(addPrefix(msg))
#define LogInfo(msg) Mylogger::getInstance()->info(addPrefix(msg))
#define LogDebug(msg) Mylogger::getInstance()->debug(addPrefix(msg))
//#define LogNotset(msg) Mylogger::getInstance()->notset(addPrefix(msg))

class Mylogger
{
public:
    static Mylogger * getInstance();
    void emerge(const char *msg);
    void fatal(const char *msg);
    void alert(const char *msg);
    void crit(const char *msg);
    void error(const char *msg);
    void warn(const char *msg);
    void notice(const char *msg);
    void info(const char *msg);
    void debug(const char *msg);
    void notset(const char *msg);

private:
    Mylogger();
    ~Mylogger();
    Mylogger(Mylogger & rhs) = delete;
    Mylogger & operator=(const Mylogger & rhs) = delete;
    // 注意第三种自动释放需要将destroy设为私有
    static void destroy();

private:
    static Mylogger * _pInstance;
    log4cpp::Category & _mycat;
};
#endif
