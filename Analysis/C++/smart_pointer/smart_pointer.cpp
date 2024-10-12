#include <iostream>
#include <memory>
using namespace std;

class T
{
public:
    T() { cout << "T()" << endl; }
    ~T() { cout << "~T()" << endl; }
};

// shared_ptr使用
void test1()
{
    cout << "test1" << endl;
    shared_ptr<int> p1(new int(1));
    cout << "p1 use count: " << p1.use_count() << endl;
    cout << "if p1 unique: " << p1.unique() << endl; 

    shared_ptr<int> p2 = p1;
    cout << "p2 use count: " << p2.use_count() << endl;
    cout << "if p2 unique: " << p2.unique() << endl;

    p2.reset(new int(2));
    cout << "p2 reset" << endl;
    cout << "p1 target: " << *p1.get() << endl;
    cout << "p2 target: " << *p2.get() << endl;
    cout << "p1 use count: " << p1.use_count() << endl;
    cout << "p2 use count: " << p2.use_count() << endl;
    cout << "if p1 unique: " << p1.unique() << endl; 
    cout << "if p2 unique: " << p2.unique() << endl;

    shared_ptr<int> p3(p1);
    cout << "p3 target: " << *p3.get() << endl;
    cout << "p3 use count: " << p3.use_count() << endl;
    cout << "if p3 unique: " << p3.unique() << endl; 

    shared_ptr<T> pt1(new T());
    shared_ptr<T> pt2 = pt1;
}

// shared_ptr初始化
// 但无法解决多控制块问题，也就是多次折构问题

// 由于不能检查指针空悬，会有二次折构的问题
// 所以不知道get()的危险性，就永远不要调用get()
// 将get()保存为裸指针或者智能指针都是很危险的
// 直接delete get()更是非常地危险
// 也不能用同一个指针初始化多个shared_ptr
void test1_1()
{
    cout << endl << "test1_1: " << endl; 
    shared_ptr<T> p1(new T());

    shared_ptr<T> p2(p1);
    
    shared_ptr<T> p3 = p1;

    shared_ptr<T> p4;
    cout << "p1 use count: " << p1.use_count() << endl;
    cout << "p1 target address: " << (uintptr_t)(p1.get()) << endl;

    // p4.reset(p1.get()); // 会引发二次折构，不建议用get()来构造其他shared_ptr
    // cout << "p4 use count: " << p4.use_count() << endl;
    // cout << "p4 target address: " << (uintptr_t)(p4.get()) << endl;

    // T* pt = p1.get();   // 很危险
    // delete pt;          // 会引发二次折构

    shared_ptr<int> p5 = make_shared<int>(1);

    // shared_ptr<int> p6 = new int(1); // 这种方法是错误的

    int* p = new int(1);
    shared_ptr<int> p7(p);
    // shared_ptr<int> p8(p); // 会引发二次折构
}

void DeleteIntPtr(int* p)
{
    cout << "1 Call DeleteIntPtr" << endl;
    delete p;
}

// shared_ptr 定义删除器
void test1_2()
{
    cout << endl << "test1_2" << endl;
    shared_ptr<int> p1(new int(1), DeleteIntPtr);

    shared_ptr<int> p2(new int(1), [](int* p){
        cout << "2 Call DeleteIntPtr" << endl;
        delete p;
    });

    shared_ptr<int> p3(new int[10], [](int* p){
        cout << "3 Call DeleteArrayPtr" << endl;
        delete[] p; 
    });

    shared_ptr<int[]> p4(new int[4]); // 合法的
}

void func(shared_ptr<int> p, int i)
{}

int g()
{
    return 1;
}

// 不能在实参中创建shared_ptr
// 可能会导致内存泄漏
void test1_3()
{
    // func(shared_ptr<int>(new int(0)), g()); // 有可能引发内存泄漏
    // 编译器实现不同，有可能 new -> g() -> throw error
    // new了内存，但没构造智能指针，导致内存泄漏
    cout << endl << "test1_3:" << endl;
    shared_ptr<int> p1(new int);
    func(p1, g());
}

class MT
{
public:
    shared_ptr<MT> GetSelf()
    {
        return shared_ptr<MT>(this);
    }
    MT() { cout << "MT()" << endl; }
    ~MT() { cout << "~MT()" << endl; }
};

class MT2 : public enable_shared_from_this<MT2>
{
public:
    shared_ptr<MT2> GetSelf()
    {
        return shared_from_this();
    }
    MT2() { cout << "MT2()" << endl; }
    ~MT2() { cout << "~MT2()" << endl; }
};

// 通过shared_from_this返回this指针
// 不要通过this构造智能指针返回，本质上还是通过裸指针多次构造智能指针
// 通过继承自enable_shared_from_this<>来实现管理快的唯一性
void test1_4()
{
    cout << endl << "test1_4:" << endl;
    shared_ptr<MT> sp1(new MT());
    // shared_ptr<MT> sp2 = sp1->GetSelf(); // 裸指针二次构造智能指针，双管理块问题

    shared_ptr<MT2> p1(new MT2());
    shared_ptr<MT2> p2 = p1->GetSelf();
}

class A;
class B;

class B
{
public:
    shared_ptr<A> aptr;
    B() { cout << "B()" << endl; }
    ~B() { cout << "~B()" << endl; }
};

class A
{
public:
    shared_ptr<B> bptr;
    A() { cout << "A()" << endl; }
    ~A() { cout << "~A()" << endl; }
};

// 避免shared_ptr的循环引用
void test1_5()
{
    cout << endl << "test1_5:" << endl;
    shared_ptr<A> ap(new A);
    shared_ptr<B> bp(new B);
    ap->bptr = bp;
    bp->aptr = ap;

    // 折构失败
}

// unique_ptr使用
// 不能直接拷贝，但能进行move
void test2()
{
    cout << endl << "test2" << endl;
    unique_ptr<T> up1(new T);
    unique_ptr<T> up2 = move(up1);
    // unique_ptr<T> up3 = up2; // 不能直接拷贝

    unique_ptr<T> up3 = make_unique<T>(); // c++14
}

// unique_ptr可以指向数组，但删除器的定义方式不同，需要在模板参数指定
// shared_ptr现在也可以指向数组的
void test2_1()
{
    cout << endl << "test2_1:" << endl;
    unique_ptr<T[]> p1(new T[3]);
    shared_ptr<T[]> p2(new T[3]); // 现在是合法的

    unique_ptr<int, void(*) (int*)> p3(new int(1), [](int* p){ delete p; });
    // unique_ptr<int> p4(new int(1), [](int* p){ delete p; }); // 不合法的
}

// weak_ptr使用
void test3()
{
    cout << endl << "test3" << endl;
    shared_ptr<int> sp(new int(10));
    weak_ptr<int> wp1(sp);
    weak_ptr<int> wp2;
    wp2 = sp;
    cout << "wp2 use count: " << wp2.use_count() << endl;

    if (wp1.expired())
        cout << "expired" << endl;
    else cout << "not expired" << endl;
}

// weak_ptr 线程安全问题
// 就是expired和lock的使用关系
// 其实lock底层就在判断控制块的强引用是否为0了
// lock已经提供了安全性，而且在多线程下，先用expired然后再lock，更会造成安全问题
// 所以如果只为了获取一个新的shared_ptr,只使用lock是更好的选择

void test3_1()
{
    cout << endl << "test3_1:" << endl;
    weak_ptr<int> wp;
    shared_ptr<int> sp(new int(1));
    wp = sp;
    {
        shared_ptr<int> temp = wp.lock();
        if (temp)
            cout << "not expired" << endl;
        else cout << "expired" << endl;
    }
}

// weak_ptr 解决shared_ptr返回指针的问题
void test3_2()
{
    cout << endl << "test3_2:" << endl;
    shared_ptr<MT2> sp = make_shared<MT2>();
    shared_ptr<MT2> sp2 = sp->GetSelf();
    // MT2继承自std::enable_shared_from_this中，在创建shared_ptr的时候就创建了weak_ptr进行观察
    // GetSelf()调用其shared_from_this()函数来调用weak_ptr的lock()，来进行锁定并返回shared_ptr类型
    // 从而实现二者维护的控制块相同的目的

    cout << "sp use count: " << sp.use_count() << endl;
    cout << "sp2 use count: " << sp2.use_count() << endl;
}

class C;
class D;

class C
{
public:
    shared_ptr<D> dptr;
    C() { cout << "C()" << endl; }
    ~C() { cout << "~C()" << endl; }
};

class D
{
public:
    weak_ptr<C> cptr;
    D() { cout << "D()" << endl; }
    ~D() { cout << "~D()" << endl; }
};

// weak_ptr 解决循环引用的问题
void test3_3()
{
    cout << endl << "test3_3:" << endl;
    shared_ptr<C> cp(new C);
    shared_ptr<D> dp(new D);
    cp->dptr = dp;
    dp->cptr = cp;
    // C: uc=1, wc=1    D:uc=2, wc=0

    // 折构顺序
    // cp回收   ->  C::uc--  ->  C内存回收(dptr回收)               ->    D::uc-- ->  
    // dp回收   ->  D::uc--  ->  D内存回收，cptr回收，D控制块回收   ->    C控制块回收  
}

int main()
{
    test1();
    test1_1();
    test1_2();
    test1_3();
    test1_4();
    test1_5();
    test2();
    test2_1();
    test3();
    test3_1();
    test3_2();
    test3_3();
    return 0;
}