#include <iostream>
#include <vector>
#include <cassert>
#include <limits>
using namespace std;

class Solution
{
public:
    static int shortestSubarray(vector<int>&, int);
};

int Solution::shortestSubarray(vector<int>& v, int val)
{
    int left = 0, right = 0;
    int min_c = numeric_limits<int>::max();
    int sum = 0;

    while (1)
    {
        if (left >= v.size() || right >= v.size() && sum < val)
            break;

        if (sum >= val)
        {
            min_c = min(min_c, right - left);
            sum -= v[left++];
        }
        else
        {
            sum += v[right++];
        }
    }
    if (min_c == numeric_limits<int>::max()) min_c = 0;
    return min_c;
}

void test()
{
    vector<int> v1 = {2,3,1,2,4,3};
    vector<int> v2 = {1,4,4};
    vector<int> v3 = {1,1,1,1,1,1,1,1};

    int val1 = 7;
    int val2 = 4;
    int val3 = 11;

    int out1 = 2;
    int out2 = 1;
    int out3 = 0;

    assert((Solution::shortestSubarray(v1, val1) == out1));
    assert((Solution::shortestSubarray(v2, val2) == out2));
    assert((Solution::shortestSubarray(v3, val3) == out3));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}