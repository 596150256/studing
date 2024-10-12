#include <iostream>
using namespace std;

class Base
{
public:
    virtual void dummy() { cout << "Base::dummy()" << endl; }
    void hello() { cout << "Base::hello()" << endl; }
};

class Derived : public Base
{
public:
    int a;
    long long b;
    Derived() : a(999), b(999) {}
    void dummy() override { cout << "Derived::dummy()" << endl; }
    void hello() { cout << "Derived::hello()" << endl; }
};

// const_cast只用于添加或删除指针或者引用的底层const、volatile
// const char*不能隐式转换成char*,可以用const_cast去除const
// 但此时去修改内存，会引发未定义的行为，导致segmentation fault
void const_cast_test()
{
    auto const_func = [] (const char* str) {
        cout << "in const_func: " << str << endl;
    };

    auto nonconst_func = [] (char* str) {
        cout << "in nonconst_func: " << str << endl;
        str[0] = '$';
        cout << "after modify: " << str << endl;
    };

    const char* const_str = "const";
    char s[] = "nonconst";
    char* nonconst_str = s;

    const_func(const_str);
    const_func(nonconst_str);
    const_func(const_cast<const char*>(nonconst_str));

    // nonconst_func(const_str);  // error: invalid conversion from 'const char*' to 'char*'
    nonconst_func(nonconst_str);
    // nonconst_func(const_cast<char*>(const_str)); // error: Segmentation fault (core dumped)
}

// dynamic_cast只能用在有虚函数的类之间，通过RTTI来实现cast
// 这里分为upcast和downcast，upcast在指针本身检查中发现后，应该可以通过静态cast直接来做
// 可以转换成void*,但反过来不行的
// 指针和引用都做，二者在错误处理上有点区别
void dynamic_cast_test()
{
    try {
        Base* pha = new Base;
        Base* phb = new Derived;
        Derived* phc = new Derived;
        Base* pb;
        Derived* pd;

        /**********************pointer**************************/
        // 1. upcast
        pb = dynamic_cast<Base*>(phc);
        if (pb == nullptr) cout << "0 Null pointer on dynamic_cast." << endl;

        pb = static_cast<Base*>(phc);
        if (pb == nullptr) cout << "1 Null pointer on static_cast." << endl;

        // 2. downcast
        pd = dynamic_cast<Derived*>(phb); // 对象检查成功
        if (pd == nullptr) cout << "2 Null pointer on dynamic_cast." << endl; 

        pd = dynamic_cast<Derived*>(pha); // 对象检查失败
        if (pd == nullptr) cout << "3 Null pointer on dynamic_cast." << endl;

        // 只能从类指针转为void*
        void* pva = nullptr;
        Base* pbd = nullptr;

        pva = dynamic_cast<void*>(pbd); // true

        // error: cannot 'dynamic_cast' 'pva' (of type 'void*') to type 'class Base*' (source is not a pointer to class)
        // pbd = dynamic_cast<Base*>(pva);

        /**********************reference************************/
        Base b1;
        Derived d1;

        // 1. upcast
        Base& br1 = dynamic_cast<Base&>(b1);
        Base& br2 = dynamic_cast<Base&>(d1);

        // 2. downcast
        // Derived& dr1 = dynamic_cast<Derived&>(b1); // false, throw std::bad_cast
        // Derived& dr2 = dynamic_cast<Derived&>(br1); // false, throw std::bad_cast
        Derived& dr3 = dynamic_cast<Derived&>(br2);

    } catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}

// static_cast能实现所有隐式类型转换及其相反转换，具体来说：
// 基础类型的转换
// 转换到右值引用
// 任意类型向void的转换，目标值求值后被抛弃
// void*转换到任何指针类型，及转换回来
// 显式调用仅有一个参数的构造函数或是转换操作符
// 还能完成类的upcast和downcast，但不会有运行时检查来保证指向对象的完整性
// 只会检查两个指针本身类型能否进行cast
void static_cast_test()
{
    double d = 3.14;
    int i = static_cast<int>(d); // i = 3

    int&& intref = static_cast<int&&>(i);
    intref = 4;
    cout << i << endl; // 4

    Base* pba = new Base();
    Derived* pbb = new Derived();
    Base* pbc = new Derived();

    Derived* pb = dynamic_cast<Derived*>(pba); // 转换失败 dynamic_cast一定会运行时检查
    if (pb == nullptr) { cout << "Null pointer on dynamic_cast.\n"; }

    pb = dynamic_cast<Derived*>(pbc); // 检查成功
    if (pb == nullptr) { cout << "Null pointer on dynamic_cast.\n"; }

    pb = static_cast<Derived*>(pba);
    if (pb == nullptr) { cout << "Null pointer on dynamic_cast.\n"; }

    pb = static_cast<Derived*>(pbc); // static_cast不管指针指向的内容是什么
    if (pb == nullptr) { cout << "Null pointer on dynamic_cast.\n"; }
}

// 这个就更离谱了，能完成任意指针类型向任意指针类型的转换，即使毫无关联
// 不会有指向内容的检查，也不会有指针本身类型的检查
void reinterpret_cast_test()
{
    class A {};
    class B {};
    A* a = new A;
    B* b = reinterpret_cast<B*>(a);

    // error: cannot 'dynamic_cast' 'a' (of type 'class reinterpret_cast_test()::A*') to type 'class reinterpret_cast_test()::B*' (source type is not polymorphic)
    // b = dynamic_cast<B*>(a); 

    // error: invalid 'static_cast' from type 'reinterpret_cast_test()::A*' to type 'reinterpret_cast_test()::B*'
    // b = static_cast<B*>(a);
}


int main()
{
    const_cast_test();
    dynamic_cast_test();
    static_cast_test();
    reinterpret_cast_test();
    return 0;
}