#include <iostream>
using namespace std;

template <typename X, typename Y>
auto add(X x, Y y)
{
    auto c = x + y;
    return c;
}

// template <typename X, typename Y>
// decltype(x + y) add(X x, Y y)
// {
//     return x + y;
// }

template <typename X, typename Y>
auto add(X x, Y y) -> decltype(x + y)
{
    return x + y;
}
