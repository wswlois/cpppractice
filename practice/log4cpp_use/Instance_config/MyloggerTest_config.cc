#include <iostream>
#include "Mylogger_config.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using namespace log4cpp;
void test0()
{
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();
    log->info("The log is info message");
    log->error("The log is error message");
    log->fatal("The log is fatal message");
    log->crit("The log is crit message");
    Mylogger::destroy();
}

void test1() 
{
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    LogInfo("The log is info message");
    LogError("The log is error message");
    LogWarn("The log is warn message");
    LogDebug("The log is debug message");
    Mylogger::destroy();
}
void test2() 
{
    printf("hello,world\n");
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    for(int i = 0; i<3000;i++){
    LogInfo("The log is info message");
    LogError("The log is error message");
    LogWarn("The log is warn message");
    LogDebug("The log is debug message");

    }
    Mylogger::destroy();
}
int main(int argc, char **argv)
{
    test2();
    cout << endl;
    return 0;
}

