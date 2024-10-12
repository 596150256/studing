#include <iostream>

using namespace std;

struct ListNode 
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void printList(ListNode* head)
{
    while (head->next)
    {
        cout << head->next->val << " -> ";
        head = head->next;
    }
    cout << "nullptr" << endl;
}

ListNode* reverseBetween(ListNode* head, int left, int right)
{
    ListNode* prev = head, *curr, *next, *tail;
    if (!head->next || left == right) return head;

    for (int i = 1; i < left; ++i)
        prev = prev->next;

    curr = prev->next;
    next = curr;
    tail = curr;

    for (int i = 0; i < right - left + 1; ++i)
    {
        curr = next;
        next = curr->next;
        curr->next = prev->next;
        prev->next = curr;
    }

    tail->next = next;
    return head;
}

int main()
{
    ListNode* head = new ListNode(0);
    head->next = new ListNode(1);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(3);
    head->next->next->next->next = new ListNode(4);
    head->next->next->next->next->next = new ListNode(5);

    printList(head);
    
    head = reverseBetween(head, 2, 4);

    printList(head);
    return 0;
}