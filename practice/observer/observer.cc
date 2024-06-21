#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <memory>
#include <thread>

using std::cout;
using std::endl;
using std::list;
using std::find;
using std::string;
using std::unique_ptr;

class Observer;

class Subject
{
public:
    virtual void attach(Observer *pObserver) = 0;
    virtual void detach(Observer *pObserver) = 0;
    virtual void notify() = 0;

    virtual ~Subject() {}
};

class ConcreteSubject
: public Subject
{
public:
    void attach(Observer *pObserver) override;
    void detach(Observer *pObserver) override; 
    void notify() override;

    void setStatus(int status)
    {
        _status = status;
    }

    int getStatus() const
    {
        return _status;
    }

private:
    list<Observer *> _obList;
    int _status;

};

class Observer
{
public:
    virtual void update(int) = 0;
    virtual ~Observer() {  }
};

class ConcreteObserver
: public Observer
{
public:
    ConcreteObserver(const string &name)
    : _name(name)
    {

    }
    void update(int value) 
    {
        cout << "ConcreteObserver " << _name << ", value = " << value << endl;
    }

private:
    string _name;
};

class ConcreteObserver2
: public Observer
{
public:
    ConcreteObserver2(const string &name)
    : _name(name)
    {

    }
    void update(int value) 
    {
        cout << "ConcreteObserver2 " << _name << ", value = " << value << endl;
    }

private:
    string _name;

};

void ConcreteSubject::attach(Observer *pObserver) 
{
    if(pObserver)
    {
        _obList.push_back(pObserver);
    }  
}

void ConcreteSubject::detach(Observer *pObserver) 
{
    if(pObserver)
    {
        _obList.remove(pObserver);  
    }
}

void ConcreteSubject::notify() 
{
    for(auto &ob : _obList)
    {
        ob->update(_status);
    }
}

void test()
{
    //using namespace std::chrono_literals;
    //std::this_thread::sleep_for(1s);
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    unique_ptr<ConcreteSubject> pSubject(new ConcreteSubject());
    unique_ptr<Observer> pObserver(new ConcreteObserver("lili"));
    unique_ptr<Observer> pObserver2(new ConcreteObserver2("lucy"));

    pSubject->setStatus(2);

    pSubject->attach(pObserver.get());
    pSubject->attach(pObserver2.get());

    pSubject->notify();

    pSubject->detach(pObserver2.get());
    pSubject->setStatus(3);
    pSubject->notify();
}
int main()
{
    test();
    return 0;
}
