#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Solution
{
public:
    static vector<int> firstAndLastPos(vector<int>&, int);
};

vector<int> Solution::firstAndLastPos(vector<int>& nums, int target)
{
    if (nums.size() == 0) return {-1, -1};

    vector<int> res(2, -1);
    int len = nums.size();
    int left = 0, right = len - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (nums[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    res[0] = left;

    left = 0, right = len - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (nums[mid] <= target) left = mid + 1;
        else right = mid - 1;
    }
    res[1] = right;

    if (nums[res[0]] != target) res[0] = -1, res[1] = -1; 
    return res;
}

void test()
{
    vector<int> v_in1 = {5, 7, 7, 8, 8, 10};
    vector<int> v_in2 = {5, 7, 7, 8, 8, 10};
    vector<int> v_in3 = {};

    int target1 = 8;
    int target2 = 6;
    int target3 = 0;

    vector<int> v_out1 = {3, 4};
    vector<int> v_out2 = {-1, -1};
    vector<int> v_out3 = {-1, -1};

    assert((Solution::firstAndLastPos(v_in1, target1) == v_out1));
    assert((Solution::firstAndLastPos(v_in2, target2) == v_out2));
    assert((Solution::firstAndLastPos(v_in3, target3) == v_out3));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}