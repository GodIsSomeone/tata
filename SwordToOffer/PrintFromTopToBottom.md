从上往下打印出二叉树的每个节点，同层节点从左至右打印。    
用栈来维护
```
/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};*/
class Solution {
public:
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        vector<int> vRet;
        if(root == nullptr) return vRet;
        queue<TreeNode*> vHead;
        vHead.push(root);
        while(!vHead.empty()) 
        { 
            TreeNode *tmp = vHead.front();
            vRet.push_back(tmp->val);
            if(tmp->left != nullptr) {
                vHead.push(tmp->left);
            }
            if(tmp->right != nullptr) {
                vHead.push(tmp->right);
            }
            vHead.pop();
        } 
        return vRet;
    }
};


```
