#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int findKthLargest(vector<int>& nums, int k, bool* flag)
{
    priority_queue<int, vector<int>, greater<int>> minHeap;
    if ((size_t)k > nums.size())
        return 0;

    for (int i = 0; i < k; ++i)
        minHeap.push(nums[i]);

    for (size_t i = k; i < nums.size(); ++i)
    {
        if (nums[i] > minHeap.top())
            minHeap.push(nums[i]);

        if (minHeap.size() > (size_t)k)
            minHeap.pop();
    }
    *flag = true;
    return minHeap.top();
}

int main()
{
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    int k = 2;
    bool flag = false;
    
    int ret = findKthLargest(nums, k, &flag);
    if (flag)
        cout << ret << endl;
    return 0;
}