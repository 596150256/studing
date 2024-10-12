#include <iostream>
#include <deque>
#include <vector>
#include <cassert>

using namespace std;

vector<int> everyDayTemp(vector<int> v)
{
    vector<int> ret(v.size(), 0);
    deque<int> deq;

    for (int i = 0; i < v.size(); ++i)
    {
        while(!deq.empty() && v[deq.back()] < v[i])
        {
            ret[deq.back()] = i - deq.back();
            deq.pop_back();
        }
        deq.push_back(i);
    }

    return ret;
}

void test()
{
    assert((everyDayTemp(vector<int>{73, 74, 75, 71, 69, 72, 76, 73}) 
                      == vector<int>{1, 1, 4, 2, 1, 1, 0, 0}));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}