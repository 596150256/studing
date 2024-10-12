/*
    Analyze the difference between std::array and traditional C array
    1. Type checking        ->  copy constructor instead of memcpy
                            ->  constructor to limit implicit type conversion
    2. Number logging       ->  .size() instead of extra size
    3. Boundary checking    ->  .at() instead of []
*/

#include <iostream>
#include <array>
using namespace std;

void test1()
{
    /* Type copy checking */
    int c_array1[3] = {1, 2, 3};
    int c_array2[3];
    memcpy(c_array2, c_array1, sizeof(c_array1));

    array<int, 3> cpp_array1 = {1, 2, 3};
    array<int, 3> cpp_array2;
    cpp_array2 = cpp_array1;

    /* Type conversion checking */
    double c_array[3] = {1.0, 2.0, 3.0};
    int* arr = reinterpret_cast<int*>(c_array);

    array<double, 3> cpp_array = {1.0, 2.0, 3.0};
    // arr = cpp_array;    compile error
    
}

void test2()
{
    /* Number logging contrast */
    int c_array[3] = {1, 2, 3};

    array<int, 3> cpp_array{1, 2, 3};
    cout << "Cpp array has size() - " << cpp_array.size() << endl;
}

void test3()
{
    /* Boundary checking contrast */
    int c_array[3] = {1, 2, 3};
    try
    {
        cout << "c_array[3]: " << c_array[3] << endl;
    } 
    catch (const out_of_range& e)
    {
        cerr << "C array: Out of range error: " << e.what() << endl;
    }
    catch (...)
    {
        cerr << "An unexpected error occured!" << endl;
    }

    array<int, 3> cpp_array = {1, 2, 3};
    try
    {
        cout << "cpp_array.at(3): " << cpp_array.at(3) << endl;
    }
    catch(const out_of_range& e)
    {
        std::cerr << "Cpp array: out of range error" << e.what() << endl;
    }
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}