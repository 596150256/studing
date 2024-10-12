#include <iostream>
#include <unordered_map>
using namespace std;
/*
template <
    class Key,
    class T,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator< std::pair<const Key, T>>
> class unordered_map;

template <
    class Key,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
> class unordered_set;
*/

struct Node
{
    int a, b;
    Node(int va, int vb) : a(va), b(vb) {}
};

class Hash
{
public:
    size_t operator() (const Node& n) const
    {
        return hash<int>()(n.a) ^ hash<int>()(n.b);
    }
};

class Equal_to
{
public:
    bool operator() (const Node& na, const Node& nb) const
    {
        return na.a == nb.a && na.b == nb.b;
    }
};


void test1()
{
    unordered_map<Node, int, Hash, Equal_to> um1;
    um1.insert(pair<Node, int>(Node(1, 2), 12));
    um1.insert(pair<Node, int>(Node(0, 0), 0));
    for (auto& p : um1)
        cout << p.first.a << " " << p.first.b << endl;
}

namespace std {
    template<>
    class hash<Node>
    {
    public:
        size_t operator() (const Node& n) const
        {
            return hash<int>()(n.a) ^ hash<int>()(n.b);
        }
    };

    template<>
    class equal_to<Node>
    {
    public:
        bool operator() (const Node& na, const Node& nb) const
        {
            return na.a == nb.a && na.b == nb.b;
        }
    };
}

void test2()
{
    unordered_map<Node, int> um2;
    um2.insert(pair<Node, int>(Node(1, 2), 12));
    um2.insert(pair<Node, int>(Node(0, 0), 0));
    for (auto& p : um2)
        cout << p.first.a << " " << p.first.b << endl;
}

int main()
{
    test1();
    test2();
    return 0;
}