#include "Mylogger.hh"
using std::cout;
using std::endl;
using std::cin;
using std::string;
using namespace log4cpp;
Mylogger * Mylogger::_pInstance = getInstance();
Mylogger * Mylogger::getInstance()
{
    if(!_pInstance)
    {
        atexit(destroy);
        _pInstance = new Mylogger();
    }
    return _pInstance;
}
Mylogger::Mylogger()
:_mycat(Category::getRoot().getInstance("mycat"))
{
    PatternLayout * ptn1 = new PatternLayout();
        ptn1->setConversionPattern("%d %c [%p] %m%n");
    PatternLayout * ptn2 = new PatternLayout();
        ptn2->setConversionPattern("%d %c [%p] %m%n");
    PatternLayout * ptn3 = new PatternLayout();
        ptn3->setConversionPattern("%d %c [%p] %m%n");
    auto pos = new OstreamAppender("console",&cout);
    pos->setLayout(ptn1);
    auto pfile = new FileAppender("fileApp","../log/mylog.log");
    pfile->setLayout(ptn2);
    auto rfile = new RollingFileAppender("rollingfileApp","../log/myrolling.log",1024,4);
    rfile->setLayout(ptn3);
    
    _mycat.setPriority(Priority::DEBUG);

    _mycat.setAppender(pos);
    _mycat.setAppender(pfile);
    _mycat.setAppender(rfile);
    cout << "Mylogger()" << endl;

}
void Mylogger::destroy(){
    if(_pInstance){
        delete _pInstance;
        _pInstance = nullptr;
    }
}
Mylogger::~Mylogger()
{
    Category::shutdown();

}
void Mylogger::emerge(const char *msg)
{
    _mycat.emerg(msg);
}
void Mylogger::fatal(const char *msg)
{
    _mycat.fatal(msg);
}
void Mylogger::alert(const char *msg)
{
    _mycat.alert(msg);
}
void Mylogger::crit(const char *msg)
{
    _mycat.crit(msg);
}
void Mylogger::error(const char *msg)
{
    _mycat.error(msg);
}
void Mylogger::warn(const char *msg)
{
    _mycat.warn(msg);
}
void Mylogger::notice(const char *msg)
{
    _mycat.notice(msg);
}
void Mylogger::info(const char *msg)
{
    _mycat.info(msg);
}
void Mylogger::debug(const char *msg)
{
    _mycat.debug(msg);
}
//void Mylogger::notset(const char *msg)
//{
//    //设置错误
//    /* _category.notset(msg); */
//}

