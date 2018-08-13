二叉搜索树    
左子树<根节点<右子树
中序遍历是有序的

```      
    bool isValidBST(TreeNode* root) {
        TreeNode *tmpNode = NULL;
        return helper(root, tmpNode);
    }
    bool helper(TreeNode* root, TreeNode* &tmpNode)
    {
        if (root == NULL)
        {
            return true;
        }
        bool left = helper(root->left, tmpNode);
        if (tmpNode != NULL && tmpNode->val >= root->val)
        {
            return false;
        }
        tmpNode = root;
        return left && helper(root->right, tmpNode);
    }
```

