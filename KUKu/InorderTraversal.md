Binary Tree Inorder Traversal

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        
        vector<int> ret;
        if(root==NULL) return ret;
        helper(root, ret);
        return ret;
    }
    void helper(TreeNode* root, vector<int>& ret)
    {
        if(root)
        {
            helper(root->left, ret);
            ret.push_back(root->val);
            helper(root->right, ret);
        }
    }
};
