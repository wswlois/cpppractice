#ifndef __MYLOGGER_H__
#define __MYLOGGER_H__
#include <iostream>                                 
#include "log4cpp/OstreamAppender.hh"
#include <log4cpp/PatternLayout.hh>
#include "log4cpp/Category.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/RollingFileAppender.hh"
#define LogEmerge log->emerge
#define LogFatal log->fatal
#define LogAlert log->alert
#define LogCrit log->crit
#define LogError log->error
#define LogWarn log->warn
#define LogNotice log->notice
#define LogInfo log->info
#define LogDebug log->debug
#define LogNotset log->notset


using namespace log4cpp;
using std::cout;
class Mylogger
{
public:
    static Mylogger * getInstance()
    {
        if(!_pInstance)
        {
            _pInstance = new Mylogger();
        }
        return _pInstance;
    }
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

private:
    static Mylogger * _pInstance;
    Category &  _category;
    PatternLayout* _layout;
    OstreamAppender* _oAppender;
    FileAppender* _fAppender;
    RollingFileAppender* _rFAppender;
    //......
};
#endif
