#include <iostream>
#include <deque>
#include <vector>
#include <cassert>

using namespace std;

vector<int> maxSlidingWindow(const vector<int>& nums, int k)
{
    vector<int> res;

    deque<int> q;
    for (int i = 0; i < k; ++i)
    {
        while (!q.empty() && nums[q.back()] < nums[i])
            q.pop_back();
        
        q.push_back(i);
    }

    res.push_back(nums[q.front()]);

    for (int i = k; i < nums.size(); ++i)
    {
        while (!q.empty() && q.front() <= i - k)
            q.pop_front();

        while (!q.empty() && nums[q.back()] < nums[i])
            q.pop_back();

        q.push_back(i);
        res.push_back(nums[q.front()]);
    }

    return res;
}

void test()
{
    assert((maxSlidingWindow({1, 3, -1, -3, 5, 3, 6, 7}, 3) == vector<int>{3, 3, 5, 5, 6, 7}));
    assert((maxSlidingWindow({1}, 1) == vector<int>{1}));
    assert((maxSlidingWindow({1, -1}, 1) == vector<int>{1, -1}));
    assert((maxSlidingWindow({9, 11}, 2) == vector<int>{11}));
    assert((maxSlidingWindow({4, -2}, 2) == vector<int>{4}));

    cout << "all pass" << endl;
}

int main()
{
    test();
    return 0;
}