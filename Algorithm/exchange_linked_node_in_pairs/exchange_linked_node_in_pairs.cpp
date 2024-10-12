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
    static vector<int> exchangeInPairs(vector<int>&);
    static Node* VtoL(vector<int>&);
    static vector<int> LtoV(Node*);
};

Node* Solution::VtoL(vector<int>& nums)
{
    Node* head = new Node(0);
    Node* curr = head;
    for (int val : nums)
    {
        curr->next = new Node(val);
        curr = curr->next;
    }

    return head;
}

vector<int> Solution::LtoV(Node* head)
{
    vector<int> res;
    Node* curr = head->next;
    while (curr)
    {
        res.push_back(curr->val);
        curr = curr->next;
    }
    return res;
}

vector<int> Solution::exchangeInPairs(vector<int>& nums)
{
    Node* head = VtoL(nums);

    Node* pre = head;
    Node* curr = pre->next;
    Node* next;

    while (curr && curr->next)
    {
        next = curr->next;
        curr->next = next->next;
        next->next = curr;
        pre->next = next;
        pre = curr;
        curr = pre->next;
    }

    return LtoV(head);
}

void test()
{
    vector<int> v_in1 = {1, 2, 3, 4};
    vector<int> v_in2 = {};
    vector<int> v_in3 = {1};
    vector<int> v_in4 = {1, 2, 3};

    vector<int> v_out1 = {2, 1, 4, 3};
    vector<int> v_out2 = {};
    vector<int> v_out3 = {1};
    vector<int> v_out4 = {2, 1, 3};

    assert((Solution::exchangeInPairs(v_in1) == v_out1));
    assert((Solution::exchangeInPairs(v_in2) == v_out2));
    assert((Solution::exchangeInPairs(v_in3) == v_out3));
    assert((Solution::exchangeInPairs(v_in4) == v_out4));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}