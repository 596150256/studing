#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

/*
template <
    class T,
    class Container = std::vector<T>
    class Compare = std::less<typename Container::value_type>
> class priority_queue;
*/

class Compare
{
public:
    bool operator() (const int& a, const int& b) const
    {
        return a > b;
    }
};

void test()
{
    priority_queue<int, vector<int>, Compare> minHeap;
    minHeap.push(3);
    minHeap.push(1);
    minHeap.push(4);

    while (!minHeap.empty())
    {
        cout << minHeap.top() << endl;
        minHeap.pop();
    }
}

int main()
{
    test();
    return 0;
}