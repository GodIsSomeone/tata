判断是否是对称树。递归判断
```
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <xutility>
#include <string>
#include<algorithm>
using namespace std;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == NULL)
        {
            return true;
        }
        TreeNode* leftTree  = root->left;
        TreeNode* rightTree = root->right;

        return isSame(leftTree, rightTree);
    }
    bool isSame(TreeNode* p, TreeNode* q) {
        if (p == NULL || q == NULL)
        {
            return p == q;
        }
        if (p->val == q->val)
        {
            return (isSame(p->left, q->right) && isSame(p->right, q->left));
        } 
        else
        {
            return false;
        }
    }
};

int main() {
    TreeNode* root = new TreeNode(2);
    TreeNode left(1);
    TreeNode right(3);
    root->left = &left;
    root->right = &right;
    cout << Solution().isSymmetric(root) << endl;
    return 0;
}
```
