// .cpp
#include <iostream>

using std::cout;
using std::endl;
class Singleton
{
public:
    class AutoRelease{
    public:
        AutoRelease()
        {
        }
        ~AutoRelease(){
            if(_pInstance) {
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };
    static Singleton *getInstance()
    {
        if(nullptr == _pInstance)
        {
            //当里面没有值选择直接默认值,后续想更改使用init进行更改
            _pInstance =  new Singleton(1,2);
        }
        return _pInstance;
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
    static AutoRelease _ar;
};
Singleton * Singleton::_pInstance = nullptr;
Singleton::AutoRelease Singleton::_ar;
int main(int argc, char **argv)
{
    //静态对象加上嵌套类实现
    Singleton::getInstance();
    Singleton::getInstance()->init(10,30);
    Singleton::destroy();
    return 0;
}

