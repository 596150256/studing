#include <iostream>
using namespace std;

class Base1
{
public:
    virtual void f() {}
    virtual void g() {}
};

class Base2
{
public:
    virtual void f() {}
    virtual void g() {}
};

class Base3
{
public:
    virtual void f() {}
    virtual void g() {}
};

class Derived : public Base1, public Base2, public Base3
{
public:
    virtual void f() {}
    virtual void g1() {}
};

int main()
{
    Base1 b;
    Derived d;
    cout << "vtpr1          address: " << (uintptr_t *)*((uintptr_t *)(&d) + 0) << endl;
    cout << " Derived::f()  address: " << (void *)*((uintptr_t *)*(uintptr_t *)(&d) + 0) << endl;
    cout << " Base1::g()    address: " << (void *)*((uintptr_t *)*(uintptr_t *)(&d) + 1) << endl;
    cout << " Derived::g1() address: " << (void *)*((uintptr_t *)*(uintptr_t *)(&d) + 2) << endl;
    cout << "vtpr1              end: " << (void *)*((uintptr_t *)*(uintptr_t *)(&d) + 3) << endl;

    cout << "vtpr2          address: " << (uintptr_t *)*((uintptr_t *)(&d) + 1) << endl;
    cout << " Derived::f()  address: " << (void *)*((uintptr_t *)*((uintptr_t *)(&d) + 1) + 0) << endl;
    cout << " Base2::g()    address: " << (void *)*((uintptr_t *)*((uintptr_t *)(&d) + 1) + 1) << endl;
    cout << "vtpr2              end: " << (void *)*((uintptr_t *)*((uintptr_t *)(&d) + 1) + 2) << endl;

    cout << "vtpr3          address: " << (uintptr_t *)*((uintptr_t *)(&d) + 2) << endl;
    cout << " Derived::f()  address: " << (void *)*((uintptr_t *)*((uintptr_t *)(&d) + 2) + 0) << endl;
    cout << " Base3::g()    address: " << (void *)*((uintptr_t *)*((uintptr_t *)(&d) + 2) + 1) << endl;
    cout << "vtpr3              end: " << (void *)*((uintptr_t *)*((uintptr_t *)(&d) + 2) + 2) << endl;

    return 0;
}