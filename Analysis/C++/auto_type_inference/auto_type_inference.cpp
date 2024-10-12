#include <iostream>
#include <typeinfo>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

// auto在使用时，必须进行初始化
void test1()
{
    cout << "test1:" << endl;
    auto a = 1;
    auto b = 3.14;
    auto c = 'c';
    // auto d; // error: declaration of 'auto d' has no initializer
}

// 与修饰符结合
// const和变量中间如果没经过&或者*，就直接作用在顶层了
// auto推导会去除顶层const，不去除底层const
// typeid输出会忽略const和引用，不去除指针
void test2()
{
    cout << endl << "test2:" << endl;
    // 与指针和引用相结合
    int temp = 1;
    auto a = temp;              // temp:int      ->  a:int         ->  auto:int
    auto& b = temp;             // temp:int      ->  b:int&        ->  auto:int             !!!auto&只是显式声明b是一个引用，typeinfo的结果会和底层temp一致，忽略引用!!!
    auto c = &temp;             // &temp:int*    ->  c:int*        ->  auto:int*
    auto* d = &temp;            // &temp:int*    ->  d:int*        ->  auto:int*            !!!auto*只是显式声明d是一个指针，typeinfo的结果不忽略指针!!!

    const auto ca = temp;       // temp:int      ->  ca:const int  ->  auto:int             !!!typeinfo忽略了const修饰符!!!
    // ca = 2; // false
    auto cb = ca;               // ca:const int  ->  cb:int        ->  auto:int             !!!auto去掉了const修饰符!!!
    cb = 2; // true

    const auto &cc = temp;      // temp:int      ->  cc:const int& ->  auto:int             !!!typeinfo忽略了引用和const!!!
    // cc = 2; // false
    auto& cd = cc;              // cc:const int& ->  cd:const int& ->  auto:int             !!!auto保留底层const，typeinfo忽略const和引用!!!
    // cd = 2; // false
    const auto da = &temp;      // &temp:int*    ->  da:int* const ->  auto:int*            !!!const跨过auto直接修饰da本体，保留指针，忽略顶层const!!!
    // da = null; // false
    auto db = da;               // da:int* const ->  db:int*       ->  auto:int*            !!!auto去掉顶层const!!!
    const auto* dc = &temp;     // &temp:int*    ->  dc:const int* ->  auto:const int*      !!!const修饰到底层，保留了底层const，typeinfo不忽略底层const和指针!!!
    auto* dd = dc;              // dc:const int* ->  dd:const int* ->  auto:const int*      !!!auto保留底层const!!!

    cout << "a: " << typeid(a).name() << endl;
    cout << "b: " << typeid(b).name() << endl;
    cout << "c: " << typeid(c).name() << endl;
    cout << "d: " << typeid(d).name() << endl;
    cout << "ca: " << typeid(ca).name() << endl;
    cout << "cb: " << typeid(cb).name() << endl;
    cout << "cc: " << typeid(cc).name() << endl;
    cout << "cd: " << typeid(cd).name() << endl;
    cout << "da: " << typeid(da).name() << endl;
    cout << "db: " << typeid(db).name() << endl;
    cout << "dc: " << typeid(dc).name() << endl;
    cout << "dd: " << typeid(dd).name() << endl;
}

template <typename T>
class C
{};
// 不能使用auto的场景
void test3()
{
    cout << endl << "test3:" << endl;
    // 1. 函数参数
    // void Add(auto, auto); // error: 'auto' parameter not permitted in this context

    // 2. 模板参数
    // C<auto> c; // error: template argument 1 is invalid

    // 3. 定义数组
    int arr1[5] = {1, 2, 3, 4, 5};
    auto arr2 = {1, 2, 3, 4, 5}; // std::initializer_list<int>

    // auto arr3[5] = {1, 2, 3, 4, 5}; // error: unable to deduce 'std::initializer_list<auto> [5]' from '{1, 2, 3, 4, 5}'
    // 相当于给std::initializer_list<>模板提供了一个auto参数

    // 4. 类的非静态成员初始化
    class D
    {
    private:
        // auto a = 10; // error: non-static data member declared with placeholder 'auto'
        // 虽然有10看似可以进行deduce，但这不是在编译阶段动作
    };
}

class foo1
{
public:
    static double get() { return 3.14; }
};

class foo2
{
public:
    static int get() { return 3; }
};

template <typename T>
auto func()
{
    auto r = T::get();
    return r;
}
// 使用场景
void test4()
{
    cout << endl << "test4:" << endl;
    // 1. 简化迭代器语法
    map<int, int> m;
    for (auto it = m.begin(); it != m.end(); ++it) {}

    // 2. 模板内变量和返回值
    auto r1 = func<foo1>(); // double
    auto r2 = func<foo2>(); // int

    cout << typeid(r1).name() << endl;
    cout << typeid(r2).name() << endl;

    // 3. lambda表达式
    vector<int> v = {1, 2, 3, 4};
    auto print = [](const int& value) { cout << value << endl; };
    for_each(v.begin(), v.end(), print);
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}