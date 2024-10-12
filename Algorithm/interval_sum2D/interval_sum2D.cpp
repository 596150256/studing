#include <iostream>
#include <vector>
#include <cassert>
#include <limits>
using namespace std;

class Solution
{
public:
    static int intervalSum2D(vector<vector<int>>&);
};

int Solution::intervalSum2D(vector<vector<int>>& nums)
{
    vector<vector<int>> sums = nums;
    int row = sums.size(), col = sums[0].size();

    for(int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
        {
            if (i == 0 && j == 0) continue;
            if (i == 0) sums[i][j] += sums[i][j - 1];
            else if (j == 0) sums[i][j] += sums[i - 1][j];
            else sums[i][j] += sums[i][j - 1] + sums[i - 1][j] - sums[i - 1][j - 1];
        }

    int min_diff = numeric_limits<int>::max();
    for (int i = 1; i < row; ++i)
        min_diff = min(min_diff, abs(sums[row - 1][col - 1] - 2 * sums[i - 1][col - 1]));

    for (int i = 1; i < col; ++i)
        min_diff = min(min_diff, abs(sums[row - 1][col - 1] - 2 * sums[row - 1][i - 1]));

    return min_diff;
}

void test()
{
    vector<vector<int>> v1 = {
        {1, 2, 3},
        {2, 1, 3},
        {1, 2, 3}
    };
    
    int res1 = 0;

    assert((Solution::intervalSum2D(v1) == res1));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}