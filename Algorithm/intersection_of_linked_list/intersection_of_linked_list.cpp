#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

struct Node
{
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

class Solution
{
public:
    static vector<int> intersectionLinkedList(vector<int>&, vector<int>&);
    static Node* VtoL(vector<int>&);
    static Node* getIntersection(Node*, Node*);
    static vector<int> NtoV(Node*);
};

Node* Solution::VtoL(vector<int>& nums)
{
    Node* head = new Node(0);
    Node* curr = head;
    for (auto val : nums)
    {
        curr->next = new Node(val);
        curr = curr->next;
    }

    return head;
}

Node* Solution::getIntersection(Node* headA, Node* headB)
{
    Node* curA = headA->next;
    Node* curB = headB->next;

    while (1)
    {
        if (!curA && !curB) return nullptr;
        if (!curA) 
        {
            curA = headB->next;
            curB = curB->next;
        }
        else if (!curB)
        {
            curB = headA->next;
            curA = curA->next;
        }
        else
        {
            if (curA->val == curB->val) return curA;
            curA = curA->next;
            curB = curB->next;
        }
    }   
}

vector<int> Solution::NtoV(Node* node)
{
    vector<int> res;
    Node* curr = node;
    while (curr)
    {
        res.push_back(curr->val);
        curr = curr->next;
    }

    return res;
}

vector<int> Solution::intersectionLinkedList(vector<int>& vA, vector<int>& vB)
{
    Node* headA = VtoL(vA);
    Node* headB = VtoL(vB);
    Node* node = getIntersection(headA, headB);
    vector<int> res = NtoV(node);
    return res;
}

void test()
{
    vector<int> vA1 = {4, 1, 8, 4, 5};
    vector<int> vA2 = {0, 9, 1, 2, 4};
    vector<int> vA3 = {2, 6, 4};

    vector<int> vB1 = {5, 0, 1, 8, 4, 5};
    vector<int> vB2 = {3, 2, 4};
    vector<int> vB3 = {1, 5};

    vector<int> out1 = {1, 8, 4, 5};
    vector<int> out2 = {2, 4};
    vector<int> out3 = {};

    assert((Solution::intersectionLinkedList(vA1, vB1) == out1));
    assert((Solution::intersectionLinkedList(vA2, vB2) == out2));
    assert((Solution::intersectionLinkedList(vA3, vB3) == out3));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}