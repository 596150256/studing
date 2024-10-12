#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

class More
{
public:
    bool operator() (const int& a, const int& b)
    {
        return a < b;
    }
};

class Less
{
public:
    bool operator() (const int& a, const int& b)
    {
        return a > b;
    }
};

// test user defined sort for vector
void test()
{
    vector<int> in1 = {3, 1, 4, 1, 5};
    vector<int> in2 = {3, 1, 4, 1, 5};

    vector<int> out1 = {1, 1, 3, 4, 5};
    vector<int> out2 = {5, 4, 3, 1, 1};

    sort(in1.begin(), in1.end(), More());
    sort(in2.begin(), in2.end(), Less());

    assert((in1 == out1));
    assert((in2 == out2));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}