#include <bits/stdc++.h>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void read_node(TreeNode **n)
{
    queue<TreeNode **> q;
    q.push(n);
    int t;
    while (!cin.eof())
    {
        cin >> t;
        if (t != -1)
        {
            *(q.front()) = new TreeNode(t);
            TreeNode *p = *(q.front());
            q.push(&(p->left));
            q.push(&(p->right));
        }
        q.pop();
    }
}

int main()
{
    TreeNode *n = NULL;
    read_node(&n);
    return 0;
}