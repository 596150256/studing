#include <iostream>
using namespace std;

class Base
{
public:
    Base() { cout << "Base()" << endl; }
    ~Base() {}

    Base(const Base&) { cout << "Base(const Base&)" << endl; }
    Base(Base&&) { cout << "Base(Base&&)" << endl; }
};

Base create1()
{
    // 如果移动构造/赋值被delete，这里不受影响，应该是编译器定义的直接构造目标对象，没有移动构造的过程
    return Base();
}

// RVO
// 通过局部对象直接构造目标对象
// 而不是拷贝构造目标对象
// gcc实现原理是将返回对象构造在调用者栈帧上，直接访问返回值
void test1()
{
    cout << "test1:" << endl;
    Base a = create1(); // Base()
    // 相当于只有 Base a(); 而不存在任何复制
}

Base create2()
{
    Base res;

    // 如果移动构造/赋值被delete，这里受到影响，虽然在NRVO作用下和test1的结果一样，但编译器仍然要求移动构造/赋值的可使用性
    return res; // error: use of deleted function 'Base::Base(Base&&)'
}

// NRVO
void test2()
{
    
    cout << endl << "test2:" << endl;
    Base a = create2(); // Base()
    // res这个明确的返回值名称会直接构造到调用方的目标对象中
    // 实现原理就是用返回对象直接替换掉res这个命名临时返回对象
}

int main()
{
    test1();
    test2();
    return 0;
}