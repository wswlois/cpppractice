#ifndef __MYLOGGER_H__
#define __MYLOGGER_H__
#include <iostream>                                 
#include <cstring>
#include <string>
#include "log4cpp/OstreamAppender.hh"
#include <log4cpp/PatternLayout.hh>
#include "log4cpp/Category.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/RollingFileAppender.hh"
#define LogEmerge(msg) (Mylogger::getInstance()->emerge(std::string(__FILE__).append(" ").append(__func__).append(" ").append(std::to_string(__LINE__)).append(msg).c_str()))
#define LogFatal(msg)  (Mylogger::getInstance()->fatal(std::string(__FILE__).append(" ").append(__func__).append(" ").append(std::to_string(__LINE__)).append(msg).c_str()))
#define LogAlert(msg) (Mylogger::getInstance()->alert(std::string(__FILE__).append(" ").append(__func__).append(" ").append(std::to_string(__LINE__)).append(msg).c_str()))
#define LogCrit(msg) (Mylogger::getInstance()->crit(std::string(__FILE__).append(" ").append(__func__).append(" ").append(std::to_string(__LINE__)).append(msg).c_str()))
#define LogError(msg) (Mylogger::getInstance()->error(std::string(__FILE__).append(" ").append(__func__).append(" ").append(std::to_string(__LINE__)).append(msg).c_str()))
#define LogWarn(msg) (Mylogger::getInstance()->warn(std::string(__FILE__).append(" ").append(__func__).append(" ").append(std::to_string(__LINE__)).append(msg).c_str()))
#define LogNotice(msg) (Mylogger::getInstance()->notice(std::string(__FILE__).append(" ").append(__func__).append(" ").append(std::to_string(__LINE__)).append(msg).c_str()))
#define LogInfo(msg) (Mylogger::getInstance()->info(std::string(__FILE__).append(" ").append(__func__).append(" ").append(std::to_string(__LINE__)).append(msg).c_str()))
#define LogDebug(msg) (Mylogger::getInstance()->debug(std::string(__FILE__).append(" ").append(__func__).append(" ").append(std::to_string(__LINE__)).append(msg).c_str()))
#define LogNotset(msg) (Mylogger::getInstance()->notset(std::string(__FILE__).append(" ").append(__func__).append(" ").append(std::to_string(__LINE__)).append(msg).c_str()))


using namespace log4cpp;
using std::cout;
using std::string;
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
