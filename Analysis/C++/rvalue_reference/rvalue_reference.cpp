/*
    右值引用
    左值引用的缺陷 -> 右值引用的便利 -> 引用折叠 -> 完美转发
*/
#include <iostream>
#include <utility>
#include <memory>
using namespace std;

class Node
{
public:
    Node() { cout << "Node()" << endl; }
    Node(const int& a, const double& b) { cout << "Node(const int&, const doube&)" << endl; }
    Node(int&& a, double&& b) { cout << "Node(int&&, double&&)" << endl; }
    ~Node() {}

    Node(const Node& n) { cout << "Node(const Node&)" << endl; }
    Node(Node&& n) noexcept { cout << "Node(Node&&)" << endl; }

    Node& operator= (const Node&) 
    { 
        cout << "operator=(const Node&)" << endl;
        return *this;    
    }
    Node& operator= (Node&&) noexcept
    {
        cout << "operator=(Node&&)" << endl;
        return *this;
    }
};

Node Copy(Node& n) // n is lvalue default
{
    Node r = n; // 拷贝构造
    return r;
}

Node Copy(Node&& n) // n is rvalue default
{
    Node r = (move(n)); // 移动构造
    return r;
}

// 说明左值引用的缺陷
// Node()
// Node(const Node&)
// 和预想少一次拷贝构造，可能是NRV优化
void test1()
{
    cout << "test1:" << endl;
    Node n;
    Node n_new = Copy(n);
}

// 右值引用的便利
// 拷贝构造即使减少到一次，但也是深拷贝
// 通过右值引用变为浅拷贝！
void test2()
{
    cout << endl << "test2:" << endl;
    Node n;

    cout << "Copy(move(n))" << endl;
    Node n_new = Copy(move(n));

    cout << "Copy(Node())" << endl;
    Node n_new2 = Copy(Node());
}

// 右值引用noexcept的必要性
// 虽然这里实验了去掉noexcept或者给拷贝构造/拷贝赋值增加noexcept都还是相同的结果
// 但还是存在退化为拷贝构造/拷贝赋值的可能
void test3()
{
    cout << endl << "test3:" << endl;
    Node n1, n2;
    swap(n1, n2); // std::swap要求右值引用的移动构造/移动赋值运算符是noexcept的
}

void process(const int&)
{
    cout << "const int&" << endl;
}

void process(int&)
{
    cout << "int&" << endl;
}

void process(int&&)
{
    cout << "int&&" << endl;
}

template <typename T>
void Test1(T&& t)
{
    process(forward<T>(t));
}

template <typename T>
void Test2(T& t)
{
    process(forward<T>(t));
}

// 说明引用折叠的各种情况
void test4()
{
    cout << endl << "test4:" << endl;
    int a = 1;
    const int b = 1;
    // &&
    Test1(1); // int            ->  int&&
    Test1(a); // int&           ->  int&
    Test1(b); // const int&     ->  const int&
    Test1(move(a)); // int&&    ->  int&&

    // &
    // Test2(1); // error: int  cannot bind non-const lvalue reference to int
    Test2(a); // int&           ->  int&&?
    Test2(b); // const int&     ->  const int&
    // Test2(move(a)); // error: cannot bind non-const lvalue reference to int&&
}

template <typename T, typename... Args>
shared_ptr<T> create(Args&&... args)
{
    return make_shared<T>(forward<Args>(args)...);
}
// 完美转发
// 探究为什么函数重载不能替代完美转发
// 主要考虑工厂函数的使用场景
// 参数的数目和类型是可变的情况下，重构工厂函数会很复杂
// 将工厂函数写成完美转发，来将参数传递给构造函数或其他函数，可以保持代码的工整
void test5()
{
    cout << endl << "test5:" << endl;
    int a = 42;
    double b = 3.14;
    auto n1 = create<Node>(a, b);       // Node(const int&, const doube&)
    auto n2 = create<Node>(42, 3.14);   // Node(int&&, double&&)

    auto n3 = create<Node>(Node());     // Node(Node&&)
    Node n;
    auto n4 = create<Node>(n);          // Node(const Node&)
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}

/* move的实现 */
template <typename T>
    struct Remove_reference
    { typedef T type; };

template <typename T>
    struct Remove_reference<T&>
    { typedef T type; };

template <typename T>
    struct Remove_reference<T&&>
    { typedef T type; };

template <typename T>
    constexpr typename Remove_reference<T>::type&&
    move1(T&& t)
    {
        return static_cast<typename Remove_reference<T>::type&&>(t);
    }

/* forward的实现 */
template <typename T>
    constexpr T&&
    forward1(typename Remove_reference<T>::type& t)
    {
        return static_cast<T&&>(t);
    }

template <typename T>
    constexpr T&&
    forward1(typename Remove_reference<T>::type&& t)
    {
        return static_cast<T&&>(t);
    }

/* emplace的实现 */
// template <typename... Args>
//     void
//     emplace(Args... args)
//     {
//         if (finish != end_of_storage)
//         {
//             construct(finish, forward<Args>(args)...);
//             ++finish;
//         }
//         else
//             emplace_aux(forward<Args>(args)...);
//     }