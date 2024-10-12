#include <iostream>
using namespace std;

class Base
{
public:
    Base() { cout << "Base()" << endl; }
    ~Base() { cout << "~Base()" << endl; }
};

class Derived : public Base
{
};

class A
{
public:
    Base base;
};

class B
{
public:
    virtual void function() {}
};

class C : public virtual Base
{
};

void test()
{
    cout << "Derived default construction start" << endl;
    Derived derived;

    cout << "A default construction start" << endl;
    A a;

    cout << "B default construction start" << endl;
    B b;

    cout << "C default construction start" << endl;
    C c;
}

int main()
{
    test();
    return 0;
}