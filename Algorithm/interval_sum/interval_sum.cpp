#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Solution
{
public:
    static int intervalSum(vector<int>&, int, int);
};

int Solution::intervalSum(vector<int>& nums, int left, int right)
{
    vector<int> sums(nums.begin(), nums.end());
    for (int i = 1; i < sums.size(); ++i)
        sums[i] += sums[i - 1];

    if (left == 0) return sums[right];
    else return sums[right] - sums[left - 1];
}

void test()
{
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {1, 2, 3, 4, 5};

    int l1 = 0, r1 = 1;
    int l2 = 1, r2 = 3;

    int res1 = 3;
    int res2 = 9;

    assert((Solution::intervalSum(v1, l1, r1) == res1));
    assert((Solution::intervalSum(v2, l2, r2) == res2));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}