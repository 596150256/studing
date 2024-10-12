#include <iostream>
#include <vector>
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

    for(auto val : v)
    {
        p->next = new ListNode(val);
        p = p->next;
    }

    return head;
}

vector<int> LtoV(ListNode* head)
{
    vector<int> ret;
    while (head->next)
    {
        ret.push_back(head->next->val);
        head = head->next;
    }

    return ret;
}

vector<int> reverseList(vector<int> v)
{
    ListNode* head = VtoL(v);

    ListNode* pre = head;
    ListNode* next = pre->next;
    ListNode* cur;
    pre->next = nullptr;

    while (next)
    {
        cur = next;
        next = cur->next;

        cur->next = pre->next;
        pre->next = cur;
    }

    return LtoV(head);
}

void test()
{
    assert((reverseList(vector<int>{1, 2, 3, 4, 5}) == vector<int>{5, 4, 3, 2, 1}));
    assert((reverseList(vector<int>{1, 2}) == vector<int>{2, 1}));
    assert((reverseList(vector<int>{}) == vector<int>{}));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}