#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Solution
{
public:
    static int insertPos(vector<int>&, int);
};

int Solution::insertPos(vector<int>& nums, int target)
{
    int len = nums.size();
    int l = 0, r = len - 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (nums[mid] == target) return mid;
        if (target > nums[mid]) l = mid + 1;
        else r = mid - 1;
    }
    return l;
}

void test()
{
    vector<int> v1 = {1, 3, 5, 6};
    vector<int> v2 = {1, 3, 5, 6};
    vector<int> v3 = {1, 3, 5, 6};

    int val1 = 5;
    int val2 = 2;
    int val3 = 7;

    int res1 = 2;
    int res2 = 1;
    int res3 = 4;

    assert((Solution::insertPos(v1, val1) == res1));
    assert((Solution::insertPos(v2, val2) == res2));
    assert((Solution::insertPos(v3, val3) == res3));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}