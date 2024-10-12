#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Solution
{
public:
    static vector<int> sortByParity(vector<int>&);
};

vector<int> Solution::sortByParity(vector<int>& nums)
{
    int evenIndex = 0;
    for (int oddIndex = 1; oddIndex < nums.size(); oddIndex += 2)
    {
        while (nums[oddIndex] % 2 == 0)
        {
            swap(nums[evenIndex], nums[oddIndex]);
            evenIndex += 2;
        }
    }

    return nums;
}

void test()
{
    vector<int> v0 = {4, 2, 5, 7};
    vector<int> v1 = {2, 3};

    vector<int> res0 = {2, 5, 4, 7};
    vector<int> res1 = {2, 3};

    assert((Solution::sortByParity(v0) == res0));
    assert((Solution::sortByParity(v1) == res1));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}