#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int maxAreaOfIsland(vector<vector<int>>& grid)
    {
        int maxArea = 0;
        int rows = grid.size();
        int cols = grid[0].size();

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
            {
                if (grid[i][j] == 1)
                {
                    int temp = dfs(grid, i, j);
                    maxArea = max(maxArea, temp);
                }
            }

        return maxArea;
    }
private:
    int dfs(vector<vector<int>>& grid, int x, int y)
    {
        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == 0)
            return 0;

        grid[x][y] = 0;

        int area = 1;
        area += dfs(grid, x - 1, y);
        area += dfs(grid, x + 1, y);
        area += dfs(grid, x, y - 1);
        area += dfs(grid, x, y + 1);

        return area;
    }
};

int main()
{
    Solution solution;
    vector<vector<int>> grid = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 0, 1, 1}
    };

    int maxArea = solution.maxAreaOfIsland(grid);
    cout << maxArea << endl;

    return 0;
}