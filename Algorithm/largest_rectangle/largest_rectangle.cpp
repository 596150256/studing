#include <iostream>
#include <deque>
#include <vector>
#include <cassert>
using namespace std;

class Solution
{
public:
    static int maxRectangle(vector<int>&);
};

int Solution::maxRectangle(vector<int>& v)
{
    v.insert(v.begin(), 0);
    v.push_back(0);
    int maxArea = 0;
    deque<int> q;

    for (int i = 0; i < v.size(); ++i)
    {
        while (!q.empty() && v[q.back()] > v[i])
        {
            int tmp = q.back();
            q.pop_back();
            maxArea = max(maxArea, v[tmp] * (i - 1 - q.back()));
        }
        q.push_back(i);
    }

    return maxArea;
}

void test()
{
    vector<int> in1 = {2, 1, 5, 6, 2, 3};
    vector<int> in2 = {2, 4};
    vector<int> in3 = {9, 0};
    vector<int> in4 = {2, 1, 2};

    int out1 = 10;
    int out2 = 4;
    int out3 = 9;
    int out4 = 3;

    assert((Solution::maxRectangle(in1) == out1));
    assert((Solution::maxRectangle(in2) == out2));
    assert((Solution::maxRectangle(in3) == out3));
    assert((Solution::maxRectangle(in4) == out4));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}