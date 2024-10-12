#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cmath>

using namespace std;

void medianOfMedian(vector<int> v, int left, int right)
{
    int n = right - left + 1;
    if (n <= 5)
    {
        sort(v.begin() + left, v.begin() + right + 1);
        swap(v[left], v[left + n / 2]);
        return;
    }

    for (int i = left; i <= right; i += 5)
    {
        int end = min(i + 4, right);
        sort(v.begin() + i, v.begin() + end + 1);
        swap(v[left + (i / 5)], v[i + (end - i + 1) / 2]);
    }

    medianOfMedian(v, left, left + ceil(n / 5) - 1);
}

void qsort(vector<int>& v, int left, int right)
{
    if (left >= right) return;

    medianOfMedian(v, left, right);

    int pivot = v[left];
    int l = left, r = right;
    while (l < r)
    {
        while (l <= r && v[l] <= pivot) l++;
        while (r >= l && v[r] > pivot) r--;
        if (l < r) swap(v[l], v[r]);
    }
    swap(v[left], v[l - 1]);

    qsort(v, left, l - 2);
    qsort(v, l, right);
}

vector<int> quickSort(vector<int> v)
{
    qsort(v, 0, v.size() - 1);

    return v;
}

void test()
{
    assert((quickSort(vector<int>{3, 5, 2, 4, 6}) == vector<int>{2, 3, 4, 5, 6}));
    assert((quickSort(vector<int>{5, 1, 3, 2, 4}) == vector<int>{1, 2, 3, 4, 5}));
    assert((quickSort(vector<int>{8, 3, 7, 1, 5}) == vector<int>{1, 3, 5, 7, 8}));
    assert((quickSort(vector<int>{10, 7, 8, 9, 1, 5}) == vector<int>{1, 5, 7, 8, 9, 10}));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}