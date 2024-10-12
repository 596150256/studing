/* 
    Analyze the difference between C string with std::string.
*/

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

void test1()
{
    /* memory management */
    char* c_str = new char(10);
    strcpy(c_str, "hello");
    cout << "C-style string: " << c_str << endl;

    try{
        strcpy(c_str, "a too long string");
    } catch (...) {
        cerr << "error!" << endl;
    }

    delete[] c_str;

    string cpp_str = "hello";
    cpp_str += "world";
    cout << "std::string: " << cpp_str << endl;
}

void test2()
{
    /* manipulation of functions: len and interconversion */
    char* c_str = new char(10);
    int c_len = strlen(c_str);

    string cpp_str = "hello";
    int cpp_len = cpp_str.size();

    const char* c_style_from_cpp = cpp_str.c_str();
    string cpp_style_from_c = string(c_str);
}

int main()
{
    test1();
    test2();
    return 0;
}