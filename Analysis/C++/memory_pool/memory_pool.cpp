#include <iostream>
using namespace std;

class A
{
public:
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
private:
   int a;
};

void test1()
{
    A* p = (A*)operator new(sizeof(A) * 10);
    for (int i = 0; i < 10; i++)
    {
        new(p + i)A();
    }

    for (int i = 0; i < 10; i++)
    {
        (p + i)->~A();
    }

    operator delete[](p);
}

int main()
{
    test1();
    return 0;
}
