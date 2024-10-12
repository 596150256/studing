#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};

ListNode* VtoL(vector<int>& v)
{
    ListNode* head = new ListNode(0);
    ListNode* p = head;

    for (auto val : v)
    {
        p->next = new ListNode(val);
        p = p->next;
    }

    return head;
}

vector<int> LtoV(ListNode* head)
{
    vector<int> v;
    
    while (head->next)
    {
        v.push_back(head->next->val);
        head = head->next;
    }

    return v;
}

void reverseList(ListNode* head)
{
    ListNode* pre = head;
    ListNode* next = pre->next;
    ListNode* curl;
    pre->next = nullptr;

    while (next)
    {
        curl = next;
        next = curl->next;
        curl->next = pre->next;
        pre->next = curl;
    }
}

vector<int> rearrangeList(vector<int> v)
{
    ListNode* head = VtoL(v);

    size_t len = v.size();
    size_t step = size_t(ceil(len / 2.0));

    ListNode* p = head;
    for (int i = 0; i < step; ++i)
        p = p->next;

    reverseList(p);
    ListNode* pre = head->next;
    ListNode* next = p->next;
    ListNode* curl;
    p->next = nullptr;

    while (next)
    {
        curl = next;
        next = curl->next;
        curl->next = pre->next;
        pre->next = curl;
        pre = pre->next->next;
    }

    return LtoV(head);
}

void test()
{
    assert((rearrangeList(vector<int>{1, 2, 3, 4}) == vector<int>{1, 4, 2, 3}));
    assert((rearrangeList(vector<int>{1, 2, 3, 4, 5}) == vector<int>{1, 5, 2, 4, 3}));
    assert((rearrangeList(vector<int>{1}) == vector<int>{1}));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}