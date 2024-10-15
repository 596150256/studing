#include <iostream>
#include <limits>
using namespace std;

#define __int64 long long

#ifdef _WIN64
    typedef unsigned __int64 size_t;
#else
    typedef unsigned int     size_t;
#endif

typedef signed char          int8_t;
typedef short                int16_t;
typedef int                  int32_t;
typedef long long            int64_t;

void test1()
{
    cout << "test1: " << endl;
    cout << "__int64:     " << sizeof(__int64) << endl;
    cout << "size_t:      " << sizeof(size_t) << endl;

    cout << "signed char: " << sizeof(signed char) << endl;
    cout << "short:       " << sizeof(short) << endl;
    cout << "int:         " << sizeof(int) << endl;
    cout << "long long:   " << sizeof(long long) << endl;
}

void safeConvert(size_t& num)
{
    if (num <= numeric_limits<int>::max()) // 隐式类型转换比较大小
    {
        int safeInt = static_cast<int>(num);
        cout << "Converted safely to int." << endl;
    }
    else
    {
        cout << "Value too large to convert to int safely." << endl;
    }
}

void test2()
{
    cout << endl << "test2: " << endl;
    size_t large = 0xfffffffffffffff0ULL;
    size_t small = 0x000000000000ffffULL;
    safeConvert(large);
    safeConvert(small);
}

int main()
{
    test1();
    test2();
    return 0;
}

