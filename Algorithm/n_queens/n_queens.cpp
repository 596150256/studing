#include <iostream>
#include <vector>
#include <cassert>
#include <string>
using namespace std;

class Solution
{
public:
    static vector<vector<string>> nQueens(int);
private:
    static void dfs(vector<string>&, vector<vector<string>>&, int, int, int, int, int);
};

vector<vector<string>> Solution::nQueens(int n)
{
    vector<string> board(n, string(n, '.'));
    vector<vector<string>> res;
    dfs(board, res, 0, n, 0, 0, 0);
    return res;
}

void Solution::dfs(vector<string>& board, vector<vector<string>>& res, int r, int n, int cols, int leftups, int leftdowns)
{
    if (r == n) 
    {
        res.push_back(board);
        return;
    }

    for (int c = 0; c < n; ++c)
    {
        if (cols & (1 << c)) continue;
        int lu = c - r < 0 ? 32 + c - r : c - r;
        int ld = c + r;
        if (leftups & (1 << lu) || leftdowns & (1 << ld)) continue;
        board[r][c] = 'Q';
        dfs(board, res, r + 1, n, cols | (1 << c), leftups | (1 << lu), leftdowns | (1 << ld));
        board[r][c] = '.';
    }
}

void test()
{
    int in1 = 4;
    int in2 = 1;

    vector<vector<string>> out1 = {
        {".Q..","...Q","Q...","..Q."},
        {"..Q.","Q...","...Q",".Q.."},
    };
    vector<vector<string>> out2 = {
        {"Q"},
    };

    assert((Solution::nQueens(in1) == out1));
    assert((Solution::nQueens(in2) == out2));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}