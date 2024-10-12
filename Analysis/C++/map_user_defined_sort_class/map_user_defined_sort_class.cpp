#include <iostream>
#include <map>
#include <cassert>
using namespace std;

/*
template <
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
> class set;

template <
    class Key, 
    class T, 
    class Compare = std::less<Key>, 
    class Allocator = std::allocator<std::pair<const key, T>>
> class map;
*/

struct Node
{
    int a, b;
    Node(int va, int vb) : a(va), b(vb) {} 
};

class Compare
{
public:
    bool operator() (const Node& na, const Node& nb) const
    {
        if (na.a != nb.a) return na.a < nb.a;
        return na.b < nb.b;
    }
};

void test()
{
    map<Node, int, Compare> m;
    m.insert(pair<Node, int>(Node(1, 2), 12));
    m.insert(pair<Node, int>(Node(1, 3), 13));
    m[Node(2, 1)] = 21;

    for (auto& p : m)
        cout << p.first.a << " " << p.first.b << endl;
}

int main()
{
    test();
    return 0;
}