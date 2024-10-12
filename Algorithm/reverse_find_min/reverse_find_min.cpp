#include <iostream>
#include <vector>

using namespace std;

int find_min(vector<int>& nums)
{
    int left = 0, right = nums.size() - 1;
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right])
            left = mid + 1;
        else
            right = mid;
    }

    return nums[left];
}

int main()
{
    vector<int> nums = {3, 4, 5, 1, 2};
    cout << find_min(nums) << endl;
    return 0;
}

