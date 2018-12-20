输入一颗二叉树的跟节点和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。   
路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。(注意: 在返回值的list中，数组长度大的数组靠前)

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
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        vector<vector<int> > vRet;
        vector<int> path;
        if(root == nullptr) return vRet;
        helper(root, expectNumber,vRet,path);
        return vRet;
    }
    void helper(TreeNode* root, int expectNumber, vector<vector<int>> &vRet, vector<int> &path)
    {
        if(root == nullptr) return; 
        path.push_back(root->val);
        if(expectNumber == root->val && root->left==nullptr && root->right == nullptr)
        {
            vRet.push_back(path);
        }
        helper(root->left, expectNumber-root->val,vRet,path);
        helper(root->right,expectNumber-root->val,vRet,path);
        path.pop_back();
    }
};

```
