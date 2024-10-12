#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
using namespace std;

class Solution
{
public:
    static int trap(vector<int>& v);
};

int Solution::trap(vector<int>& v)
{
    stack<int> s;
    if (v[0] != 0) s.push(0);
    int res = 0;

    for (int i = 1; i < v.size(); ++i)
    {
        if (v[i] == 0) continue;
        
        int last = 0;
        while (!s.empty() && v[i] >= v[s.top()])
        {
            res += (v[s.top()] - last) * (i - s.top() - 1);
            last = v[s.top()];
            s.pop();
        }
        if (!s.empty())
            res += (v[i] - last) * (i - s.top() - 1);

        s.push(i);
    }
    return res;
}

void test()
{
    vector<int> in1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    vector<int> in2 = {4, 2, 0, 3, 2, 5};

    int out1 = 6;
    int out2 = 9;

    assert((Solution::trap(in1) == out1));
    assert((Solution::trap(in2) == out2));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}