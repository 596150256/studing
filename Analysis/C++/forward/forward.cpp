#include <iostream>
#include <typeinfo>
#include <utility>
using namespace std;

// forward函数的输入是如何进行模板特化
// 然后又如何通过引用折叠转发出去的
void process(const int& x)
{
    cout << "int&" << endl;
}

void process(const int&& x)
{
    cout << "int&&" << endl;
}

template <typename T>
T&& my_forward(typename remove_reference<T>::type& arg) noexcept {
    return static_cast<T&&>(arg);
} // T是最开始的类型，然后去掉引用，然后加上左值引用，来接收必然的左值引用
// 返回的时候用基础类型的引用折叠来完美转发，这里没有命名变量，所以完美

template <typename T> // int& int&& const& const int&&
void transfer(T&& a)
{
    // 但a作为命名变量，是一个左值
    process(my_forward<T>(a));
}

void test()
{
    int a = 10;
    const int b = 20;
    transfer(a);   // int&
    transfer(10);  // int&&
    transfer(b);   // const int&
    transfer(move(b));  // const int&&
}

int main()
{
    test();
    return 0;    
}