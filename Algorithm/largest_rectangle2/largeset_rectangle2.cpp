#include <iostream>
#include <vector>
#include <cassert>
#include <deque>
#include <string>
using namespace std;

class Solution
{
public:
    static int maxRectangle2D(vector<vector<string>>&);
    static int maxRectangle(vector<int>&);
};

int Solution::maxRectangle2D(vector<vector<string>>& vs)
{
    vector<vector<int>> vi(vs.size(), vector<int>(vs[0].size() + 2, 0));
    for (int i = 0; i < vs[0].size(); ++i)
    {
        if (vs[0][i] == "0") vi[0][i + 1] = 0;
        else vi[0][i + 1] = 1;
    }

    for (int i = 1; i < vs.size(); ++i)
    {
        for (int j = 0; j < vs[0].size(); ++j)
        {
            if (vs[i][j] == "0") vi[i][j + 1] = vi[i - 1][j + 1];
            else vi[i][j + 1] = vi[i - 1][j + 1] + 1;
        }
    }

    int maxArea = 0;
    for (int i = 0; i < vs.size(); ++i)
        maxArea = max(maxArea, maxRectangle(vi[i]));

    return maxArea;
}

int Solution::maxRectangle(vector<int>& v)
{
    int maxArea = 0;
    deque<int> q;

    for (int i = 0; i < v.size(); ++i)
    {
        while (!q.empty() && v[i] < v[q.back()])
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
    vector<vector<string>> in1 = {
        {"1","0","1","0","0"},
        {"1","0","1","1","1"},
        {"1","1","1","1","1"},
        {"1","0","0","1","0"}
    };
    vector<vector<string>> in2 = {
        {"0"}
    };
    vector<vector<string>> in3 = {
        {"1"}
    };

    int out1 = 6;
    int out2 = 0;
    int out3 = 1;

    assert((Solution::maxRectangle2D(in1) == out1));
    assert((Solution::maxRectangle2D(in2) == out2));
    assert((Solution::maxRectangle2D(in3) == out3));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}