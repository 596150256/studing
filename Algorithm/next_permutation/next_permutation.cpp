#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;

class Solution
{
public:
    static vector<int> next_permutation(vector<int>&);
};


vector<int> Solution::next_permutation(vector<int>& v)
{
    int i = v.size() - 2;
    while (i >= 0 && v[i] >= v[i + 1]) i--;

    if (i >= 0)
    {
        int j = v.size() - 1;
        while (v[j] <= v[i]) j--;
        swap(v[i], v[j]);
    }

    sort(v.begin() + i + 1, v.end());
    return v;
}

void test()
{
    vector<int> in1 = {1, 2, 3};
    vector<int> in2 = {3, 2, 1};
    vector<int> in3 = {1, 1, 5};

    vector<int> out1 = {1, 3, 2};
    vector<int> out2 = {1, 2, 3};
    vector<int> out3 = {1, 5, 1};
    
    assert((Solution::next_permutation(in1) == out1));
    assert((Solution::next_permutation(in2) == out2));
    assert((Solution::next_permutation(in3) == out3));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}