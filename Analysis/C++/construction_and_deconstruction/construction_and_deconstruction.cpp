#include <iostream>
using namespace std;

class A
{
public:
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
};

class B
{
public:
    B(int b) { cout << "B(" << b << ")" << endl; }
    ~B() { cout << "~B()" << endl; }
};

class C
{
public:
    C(int c) { cout << "C(" << c << ")" << endl; }
    ~C() { cout << "~C()" << endl;}
};

class D
{
public:
    D() { cout << "D()" << endl; }
    ~D() { cout << "~D()" << endl; }
};

class E : public A, public B
{
public:
    E() : c(3), B(5) { cout << "E()" << endl; }
    ~E() { cout << "~E()" << endl; }

private:
    C c;
    D d;
};

void test()
{
    E e;
}

int main()
{
    test();
    return 0;
}