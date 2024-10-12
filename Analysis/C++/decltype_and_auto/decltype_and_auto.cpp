#include <iostream>
using namespace std;

void test1()
{
    int i = 0;
    const int ci = i;
    const int& cir = ci;

    auto a1 = ci;   //  int
    auto a2 = cir;  //  int   由于没声明a2是引用，所以这里在分析初始值的时候，忽略了引用
    auto a3 = &i;   //  int*
    auto a4 = &ci;  //  const int*   const是底层修饰，被保留

    // 如果需要推断出的是顶层const，需要明确指出
    const auto a5 = ci;     // const int
    auto* const a6 = &i;    // int* const
    const auto* a7 = &i;    // const int*

    // 引用也可以
    auto& b1 = i;           // int&
    auto&& b2 = 42;         // int&&
    auto& const b3 = i;     // int&
    const auto& b4 = i;     // const int&
}

// 与auto不同，decltype的结果类型与表达式形式密切相关
// 引用从来都是作为指向对象的同义词出现，但只有在decltype的表达式分析上出现例外
void test2()
{
    const int ci = 0;
    const int& cj = ci;
    decltype(ci) x = 0;     // const int
    decltype(cj) y = x;     // const int&
    // decltype(cj) z;      // error: 'z' declared as reference but not initialized

    decltype((ci)) z = x;   // const int&   多了一个括号就变成引用了
    decltype(&ci) k;        // const int*
    int i = 0;
    int* p = &i;
    decltype(*p) k2 = i;    // int&         这里的解引用操作导致变成了引用类型
    
}

int main()
{
    test1();
    test2();
    return 0;
}