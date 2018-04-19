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
    bool hasPathSum(TreeNode* root, int sum) {
        if (root == NULL)
        {
            return false;
        }
        if (root->val == sum && root->right == NULL && root->left == NULL)
        {
            return true;
        }
        return hasPathSum(root->right, sum - root->val) || hasPathSum(root->left, sum - root->val);
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
     TreeNode left(2);
//     TreeNode right(3);
     root->left = &left;
//     root->right = &right;
    cout << Solution().hasPathSum(root,1) << endl;
    return 0;
}
