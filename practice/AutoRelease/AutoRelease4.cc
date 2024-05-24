// .cpp
#include <stdlib.h>
#include <pthread.h>
#include <iostream>

using std::cout;
using std::endl;
class Singleton
{
public:
    static Singleton *getInstance()
    {
        pthread_once(&_once, init_r);

        return _pInstance;
    }
    static void init_r(){
        _pInstance =  new Singleton(1,2);
        atexit(destroy);

    }
    static void destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
    void init(int x, int y)
    {
        _ix = x;
        _iy = y;
    }
    void print(){
        cout << '(' << this->_ix
            << ',' << this->_iy
            << ')' << endl;
    }
private:
    //Singleton() = default;也可以//c++11起里面使用
    Singleton()
    {}
    Singleton(int x, int y)
        :_ix(x)
         ,_iy(y)
    {}
    ~Singleton(){}
    Singleton(const Singleton & rhs) = delete;
    Singleton & operator=(const Singleton & rhs) = delete;
private:
    int _ix;
    int _iy;
    static Singleton * _pInstance;
    static pthread_once_t _once;
};
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;
Singleton * Singleton::_pInstance = nullptr;
int main(int argc, char **argv)
{
    //静态对象加上嵌套类实现
    Singleton::getInstance();
    Singleton::getInstance()->init(10,50);
    Singleton::getInstance()->print();
    Singleton::destroy();
    return 0;
}

