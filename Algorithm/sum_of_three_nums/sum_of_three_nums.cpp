#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;

class Solution
{
public:
    static vector<vector<int>> sumThreeNums(vector<int>&);
};

vector<vector<int>> Solution::sumThreeNums(vector<int>& nums)
{
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    for (int i = 0; i < nums.size(); ++i)
    {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        if (nums[i] > 0) break;

        int l = i + 1, r = nums.size() - 1;
        while (l < r)
        {
            if (nums[i] + nums[l] > 0) break;
            if (nums[i] + nums[l] + nums[r] < 0) l++;
            else if (nums[i] + nums[l] + nums[r] > 0) r--;
            else
            {
                res.push_back({nums[i], nums[l], nums[r]});
                while (l + 1 < nums.size() && nums[l + 1] == nums[l]) l++;
                l++;
                while (r - 1 >= 0 && nums[r - 1] == nums[r]) r--;
                r--;
            }
        }
    }
    return res;
}

void test()
{
    vector<int> in1 = {-1, 0, 1, 2, -1, -4};
    vector<int> in2 = {0, 1, 1};
    vector<int> in3 = {0, 0, 0};

    vector<vector<int>> out1 = {
        {-1, -1, 2},
        {-1, 0, 1}
    };
    vector<vector<int>> out2 = {};
    vector<vector<int>> out3 = {
        {0, 0, 0}
    };

    assert((Solution::sumThreeNums(in1) == out1));
    assert((Solution::sumThreeNums(in2) == out2));
    assert((Solution::sumThreeNums(in3) == out3));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}