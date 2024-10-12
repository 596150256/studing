#include <iostream>
#include <unordered_map>
#include <vector>
#include <deque>
#include <cassert>

using namespace std;

vector<int> nextLargerElem2(vector<int> v)
{
    vector<int> ret(v.size(), -1);
    deque<int> deq;

    for(int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < v.size(); ++j)
        {
            while(!deq.empty() && v[deq.back()] < v[j])
            {
                ret[deq.back()] = v[j];
                deq.pop_back();
            }
            deq.push_back(j);
        }
    }

    return ret;
}

void test()
{
    assert((nextLargerElem2(vector<int>{1, 2, 1}) == vector<int>{2, -1, 2}));

    cout << "all pass" << endl;
}

int main()
{
    test();
    return 0;
}