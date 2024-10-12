#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
using namespace std;

class Solution
{
public:
    static vector<int> numberLessThanCurr(vector<int>&);
};

vector<int> Solution::numberLessThanCurr(vector<int>& nums)
{
    vector<int> count(101, 0);
    for (auto val : nums) count[val]++;

    unordered_map<int, int> m;
    int sum = 0;
    for (int i = 0; i < 101; ++i)
    {
        if (count[i]) {
            m[i] = sum;
            sum += count[i];
        }
    }

    vector<int> res(nums.size(), 0);
    for (int i = 0; i < res.size(); ++i)
        res[i] = m[nums[i]];

    return res;
}

void test()
{
    vector<int> v_in1 = {8, 1, 2, 2, 3};
    vector<int> v_in2 = {6, 5, 4, 8};
    vector<int> v_in3 = {7, 7, 7, 7};

    vector<int> v_out1 = {4, 0, 1, 1, 3};
    vector<int> v_out2 = {2, 1, 0, 3};
    vector<int> v_out3 = {0, 0, 0, 0};

    assert((Solution::numberLessThanCurr(v_in1) == v_out1));
    assert((Solution::numberLessThanCurr(v_in2) == v_out2));
    assert((Solution::numberLessThanCurr(v_in3) == v_out3));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}