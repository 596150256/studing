#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Solution
{
public:
    static vector<vector<int>> permute(vector<int>& nums);
    static void fullPermutation(vector<int>&, vector<bool>&, vector<int>&, vector<vector<int>>&);
};

vector<vector<int>> Solution::permute(vector<int>& nums)
{
    vector<vector<int>> ret;
    vector<int> tmp;
    vector<bool> visited(nums.size(), false);
    fullPermutation(nums, visited, tmp, ret);

    return ret;
}

void Solution::fullPermutation(vector<int>& nums, vector<bool>& visited, vector<int>& tmp, vector<vector<int>>& ret)
{
    if (tmp.size() == nums.size())
    {
        ret.push_back(tmp);
        return;
    }

    for (int i = 0; i < nums.size(); ++i)
    {
        if (visited[i] == false)
        {
            visited[i] = true;
            tmp.push_back(nums[i]);
            fullPermutation(nums, visited, tmp, ret);
            tmp.pop_back();
            visited[i] = false;
        }
    }
}

void test()
{
    vector<int> in1 = {1, 2, 3};
    vector<int> in2 = {0, 1};
    vector<int> in3 = {1};

    vector<vector<int>> out1 = {
        {1, 2, 3},
        {1, 3, 2},
        {2, 1, 3},
        {2, 3, 1},
        {3, 1, 2},
        {3, 2, 1}
    };
    vector<vector<int>> out2 = {
        {0, 1},
        {1, 0}
    };
    vector<vector<int>> out3 = {
        {1}
    };

    assert((Solution::permute(in1) == out1));
    assert((Solution::permute(in2) == out2));
    assert((Solution::permute(in3) == out3));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}