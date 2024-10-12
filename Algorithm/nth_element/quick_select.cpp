#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int medianOfMedians(vector<int>& nums, int left, int right)
{
    int n = right - left + 1;
    if (n < 5)
    {
        sort(nums.begin() + left, nums.begin() + right + 1);
        swap(nums[left + n / 2], nums[left]);
        return nums[left];
    }

    for (int i = 0; i < n / 5; ++i)
    {
        int start = left + i * 5;
        int end = start + 4;
        sort(nums.begin() + start, nums.begin() + end + 1);
        swap(nums[left + i], nums[start + 2]);
    }

    return medianOfMedians(nums, left, left + n / 5 - 1);
}

int quickSelect(vector<int>& nums, int left, int right, int k)
{
    if (left == right) return nums[left];

    int pivot = medianOfMedians(nums, left, right);

    int l = left, r = right;
    while (l < r)
    {
        while (l <= nums.size() && nums[l] <= pivot) l++;
        while (r >= 0 && nums[r] > pivot) r--;
        if (l < r) swap(nums[l], nums[r]);
    }
    swap(nums[left], nums[l - 1]);

    if (k == l - 1) return nums[l - 1];
    else if (k > l - 1) return quickSelect(nums, l, right, k);
    else return quickSelect(nums, left, l - 2, k);
}

int findKthLargest(vector<int>& nums, int k, bool* flag)
{
    if (k - 1 >= nums.size())
        return 0;
    else
    {
        *flag = true;
        return quickSelect(nums, 0, nums.size() - 1, k - 1);
    }
}

int main()
{
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    int k = 2;
    bool flag = false;

    int ret = findKthLargest(nums, nums.size() - k, &flag);
    if (flag)
        cout << ret << endl;
    
    return 0;
}