#include <iostream>
#include <vector>
#include <cassert>
#include <deque>

using namespace std;

class ListNode
{
public:
    int val;
    ListNode* left, *right;
    ListNode(int v) : val(v), left(nullptr), right(nullptr) {}

    static int solution(vector<int>, int, int);
    static ListNode* VtoN(vector<int>&);
    static ListNode* ItoN(ListNode*, int);
    static ListNode* commonAncestor(ListNode*, ListNode*, ListNode*);
};

int ListNode::solution(vector<int> v, int p, int q)
{
    ListNode* head = VtoN(v);
    ListNode* p_ptr = ItoN(head, p);
    ListNode* q_ptr = ItoN(head, q);
    ListNode* ret = commonAncestor(head, p_ptr, q_ptr);
    return ret->val;
}

ListNode* ListNode::VtoN(vector<int>& v)
{
    if (v.size() == 0) return nullptr;

    deque<ListNode*> q;
    ListNode* head = new ListNode(v[0]);
    q.push_back(head);

    int i = 1;
    while (i < v.size())
    {
        if (q.front()->val == -1)
        {
            q.pop_front();
            i += 2;
            continue;
        }
            
        ListNode* tmp = new ListNode(v[i]);
        q.push_back(tmp);
        if (v[i] != -1) q.front()->left = tmp;

        if (i + 1 < v.size())
        {
            ListNode* tmp = new ListNode(v[i + 1]);
            q.push_back(tmp);
            if (v[i + 1] != -1) q.front()->right = tmp;
        }
        q.pop_front();
        i += 2;
    }

    return head;
}

ListNode* ListNode::ItoN(ListNode* head, int p)
{
    if (!head || head->val == p) return head;

    ListNode* l = ItoN(head->left, p);
    ListNode* r = ItoN(head->right, p);

    if (l) return l;
    if (r) return r;
    return nullptr;
}

ListNode* ListNode::commonAncestor(ListNode* head, ListNode* p, ListNode* q)
{
    if (!head || head == p || head == q) return head;

    ListNode* l = commonAncestor(head->left, p, q);
    ListNode* r = commonAncestor(head->right, p, q);

    if (l && r) return head;
    if (l && !r) return l;
    if (r) return r;
    return nullptr;
}

void test()
{
    assert((ListNode::solution(vector<int>{3,5,1,6,2,0,8,-1,-1,7,4}, 5, 1) == 3));
    assert((ListNode::solution(vector<int>{3,5,1,6,2,0,8,-1,-1,7,4}, 5, 4) == 5));
    assert((ListNode::solution(vector<int>{1, 2}, 1, 2) == 1));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}