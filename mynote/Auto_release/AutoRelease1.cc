// .cpp
#include <iostream>

using std::cout;
using std::endl;
class Singleton
{
public:
    static Singleton *getInstance()
    {
        if(nullptr == _pInstance)
        {
            //当里面没有值选择直接默认值,后续想更改使用init进行更改
            _pInstance =  new Singleton(1,2);
        }
        return _pInstance;
    }
    /* static void destroy() */
    /* { */
    /*     if(_pInstance) */
    /*     { */
    /*         delete _pInstance; */
    /*         _pInstance = nullptr; */
    /*     } */
    /* } */
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
    friend class AutoRelease;
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
};
Singleton * Singleton::_pInstance = nullptr;
class AutoRelease{
public:
    AutoRelease(Singleton * p)
    :_p(p)
    {
        cout << "AutoRelease(Singleton *)" <<endl;

    }
    ~AutoRelease(){
        if(_p){
            //这里调用了Singleton私有的析构函数
            //所以需要友元声明
            delete _p;
            _p = nullptr;
        }
    }
private:
    Singleton * _p;
};
int main(int argc, char **argv)
{
    //第一种自动释放方式不够完善
    //就算删除了destroy函数,还要担心多个AutoRelease共同托管
    AutoRelease autoR(Singleton::getInstance());
    /* AutoRelease autoR2(Singleton::getInstance()); */
    

    Singleton *ps1 = Singleton::getInstance();
    Singleton *ps2 = Singleton::getInstance();
    return 0;
}

