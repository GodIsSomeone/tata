判断是否有路径

```
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (NULL == root) return false;
        if (root->left==NULL && root->right==NULL && root->val==sum) return true;
        return hasPathSum(root->left, sum-root->val) || hasPathSum(root->right, sum-root->val);
    }
};

```

PathSum II
输出路径

```
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> ret;
        if(root==NULL) return ret;
        vector<int>item;
        helper(root, sum, item, ret);  
        return ret;
    }
    void helper(TreeNode* root, int sum, vector<int>& item, vector<vector<int>>& ret)
    {
        if(root==NULL) return;
        item.push_back(root->val);
        if(root->right==NULL&&root->left==NULL&& sum ==root->val) 
        {
            ret.push_back(item);
        }
        helper(root->left, sum-root->val, item, ret);
        helper(root->right, sum-root->val, item, ret);
        //  作为静态变量存储需要恢复现场
        item.pop_back();//很关键
    }
};

```


