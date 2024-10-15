#include <iostream>
using namespace std;

#ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void *)0)
    #endif
#endif

void process(int a)
{
    cout << "int" << endl;
}

void process(void* ptr)
{
    cout << "ptr" << endl;
}

void process_int(int a)
{
    cout << "int" << endl;
}

void test1()
{
    cout << "test1: " << endl;
    // process(NULL);  // error: call of overloaded 'process(NULL)' is ambiguous
}

void test2()
{
    cout << "test2: " << endl;
    process(nullptr);

    // process_int(nullptr); // error: cannot convert 'std::nullptr_t' to 'int'
}

int main()
{
    test1();
    test2();
    return 0;
}