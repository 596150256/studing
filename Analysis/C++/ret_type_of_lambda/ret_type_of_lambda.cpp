#include <iostream>
#include <typeinfo>
#include <string>
using namespace std;

template <typename T>
T f();

auto f2(int n)
{
    return n;
}

auto f3(bool b)
{
    if (b) return 1.0;
    else return 2.0;
}

auto f4(int n)
{
    if (n == 0) return 1;
    else return n * f4(n - 1);
}

struct S
{
    int n1, n2;
    decltype(auto) f6(bool b)
    {
        if (b) return (n1);
        else return (n2);
    }
};

int main()
{
    auto f1 = [] (int a) { cout << a; };
    auto f5 = [] (auto a, auto b) { return a + b; };
    f<decltype(f1(1))>();           // f1 void f<void>()
    f<decltype(f2(1))>();           // f2 int f<int>()
    f<decltype(f3(false))>();       // f3 double f<double>()
    f<decltype(f4(3))>();           // f4 int f<int>()
    f<decltype(f5(1.0, 3.0))>();    // f5 double f<double>()
    S s;
    f<decltype(s.f6(false))>();     // f6 int& f<int&>()
    return 0;
}
