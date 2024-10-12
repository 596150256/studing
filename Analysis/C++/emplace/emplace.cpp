#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <complex>
using namespace std;

// 转发与原地构造
// emplace通过变参模板，实现了原地构造，防止了隐式调用非explicit构造函数构造临时变量
void test1()
{
    struct Bar
    {
        Bar(int a) {}
        explicit Bar(int a, double b) {}
    };

    vector<Bar> bv;
    bv.push_back(1); // 通过非explicit隐式构造临时变量
    bv.push_back(Bar(1)); // 显式构造临时变量

    // bv.push_back({1, 3.14}); // 无法调用explicit隐式构造函数
    bv.push_back(Bar(1, 3.14)); // 显示构造临时变量

    bv.emplace_back(1); // 传递参数，在内存上调用构造函数，无临时变量
    bv.emplace_back(1, 3.14); // 同上
}

// map的变参构造key和value特殊情况
void test2()
{
    map<string, complex<double>> msd;

    // msd.emplace("hello", 1, 2);  // 无法区分参数的归属
    msd.insert({"hello1", {1, 2}});

    // 通过tuple将参数进行组合，但不得不构造tuple对象
    // msd.emplace(make_tuple("hello"), make_tuple(1, 2)); // tuple会被当成key和value导致错误

    // C++11设计了piecewise_construct_t类型来解决这个问题
    // 这是一个空类，std::piecewise_construct是这个类的一个对象
    msd.emplace(piecewise_construct,
                make_tuple("hello2"),
                make_tuple(1, 2));
    // 另一种写法
    msd.emplace(piecewise_construct,
                forward_as_tuple("hello3"),
                forward_as_tuple(1, 2));

    for (auto& p : msd)
        cout << p.first << endl;
}

int main()
{
    test1();
    test2();
    return 0;
}