#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> topological_sort(vector<vector<int>>& v, int n, bool* flag)
{
    vector<int> in_degree(n, 0);
    for (int i = 0; i < n; ++i)
        for (auto iter = v[i].begin(); iter != v[i].end(); iter++)
            in_degree[*iter]++;

    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (in_degree[i] == 0)
            q.push(i);

    vector<int> ret;
    while (!q.empty())
    {
        int t = q.front();
        ret.push_back(t);
        q.pop();

        for (auto iter = v[t].begin(); iter != v[t].end(); iter++)
            if(--in_degree[*iter] == 0)
                q.push(*iter);
    }

    if (ret.size() != size_t(n)) return vector<int>();

    *flag = true;
    return ret;
}

void print(vector<int>* v)
{
    for(auto iter = (*v).begin(); iter != (*v).end(); ++iter)
        cout << *iter << " ";
    cout << endl;
}

void test()
{
    int n;
    cin >> n;
    vector<vector<int>> v(n);

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        v[a].emplace_back(b);
    }
    vector<int> ret;
    bool flag = false;
    ret = topological_sort(v, n, &flag);
    print(&ret);
}

int main()
{
    test();
    return 0;
}