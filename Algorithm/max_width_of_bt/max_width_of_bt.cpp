#include <iostream>
#include <deque>
#include <vector>
#include <cassert>

using namespace std;

struct BTNode
{
    int val;
    BTNode* left;
    BTNode* right;
    BTNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

BTNode* VtoBT(vector<int>& v)
{
    if (v.empty()) return nullptr;

    deque<BTNode*> q;
    BTNode* root = new BTNode(v[0]);
    q.push_back(root);
    int i = 1;

    while (i < v.size())
    {
        if (q.front()->val == NULL)
        {
            q.pop_front();
            continue;
        }

        q.front()->left = new BTNode(v[i++]);
        q.push_back(q.front()->left);

        if (i < v.size())
        {
            q.front()->right = new BTNode(v[i++]);
            q.push_back(q.front()->right);
        }
        q.pop_front();
    }
    return root;
}

int getMaxWidthBT(BTNode* root)
{
    int max_width = 0;
    deque<pair<BTNode*, int>> q;
    q.push_back({root, 0});

    while (!q.empty())
    {
        int count = q.size(), first = q.front().second, index;

        for (int i = 0; i < count; ++i)
        {
            BTNode* tmp = q.front().first;
            index = q.front().second;
            if (tmp->left) q.push_back({tmp->left, index * 2 - first * 2});
            if (tmp->right) q.push_back({tmp->right, index * 2 + 1 - first * 2});

            q.pop_front();
        }
        max_width = max(max_width, index - first + 1);
    }

    return max_width;
}

int maxWidthOfBT(vector<int> v)
{
    BTNode* root = VtoBT(v);
    return getMaxWidthBT(root);
}

void test()
{
    assert((maxWidthOfBT(vector<int>{1, 3, 2, 5, 3, NULL, 9}) == 4));
    assert((maxWidthOfBT(vector<int>{1, 3, 2, 5}) == 2));
    assert((maxWidthOfBT(vector<int>{1, 3, 2, 5, NULL, NULL, 9, 6, NULL, 7}) == 7));

    cout << "all passed" << endl;
}

int main()
{
    test();
    return 0;
}