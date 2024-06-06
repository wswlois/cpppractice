// .cpp
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;
class Singleton
{
public:
    static Singleton *getInstance()
    {
        //当多线程同事进入if语句，可能导致单例对象被创建多个
        //但最终只有一个地址值会被_pInstance保存
        //其他的都泄露了，使用饿汉式解决
        if(nullptr == _pInstance)
        {
            atexit(destroy);
            //当里面没有值选择直接默认值,后续想更改使用init进行更改
            _pInstance =  new Singleton(1,2);
        }
        return _pInstance;
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
    //注意，这个要被设为私有，否则多线程会有destroy后重新创建后的危险
    static void destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
    Singleton(const Singleton & rhs) = delete;
    Singleton & operator=(const Singleton & rhs) = delete;
private:
    int _ix;
    int _iy;
    static Singleton * _pInstance;
};
//饱汉式（懒汉式），一开始不创建，后来用才创建
//Singleton * Singleton::_pInstance = nullptr;
//饿汉式，没有对象也会先创建
//注意下，这里直接调用getInstance()也可以，但其实是由于前面对象加了Singeton::否则也需要加
Singleton * Singleton::_pInstance = getInstance();
int main(int argc, char **argv)
{
    //静态对象加上嵌套类实现
    Singleton::getInstance();
    Singleton::getInstance()->init(10,50);
    Singleton::getInstance()->print();
    return 0;
}

