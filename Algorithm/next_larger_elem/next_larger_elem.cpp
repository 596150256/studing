#include <iostream>
#include <unordered_map>
#include <vector>
#include <deque>
#include <cassert>

using namespace std;

vector<int> nextLargerElem(vector<int> v1, vector<int> v2)
{
    vector<int> ret;
    deque<int> deq;
    unordered_map<int, int> m;

    for (int i = 0; i < v2.size(); ++i)
    {
        while (!deq.empty() && v2[deq.back()] < v2[i])
        {
            m[v2[deq.back()]] = v2[i];
            deq.pop_back();
        }
        deq.push_back(i);
    }

    for (auto val : v1)
    {
        if (m.find(val) != m.end())
            ret.push_back(m[val]);
        else
            ret.push_back(-1);
    }

    return ret;
}

void test()
{
    assert((nextLargerElem(vector<int>{4, 1, 2}, vector<int>{1, 3, 4, 2}) == vector<int>{-1, 3, -1}));
    assert((nextLargerElem(vector<int>{2, 4}, vector<int>{1, 2, 3, 4}) == vector<int>{3, -1}));

    cout << "all pass" << endl;
}

int main()
{
    test();
    return 0;
}