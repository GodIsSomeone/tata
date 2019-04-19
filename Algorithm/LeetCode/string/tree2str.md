#### 树转换成string，树的中序遍历

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
    string tree2str(TreeNode* t) {
        if(!t) return "";

        string s = to_string(t->val);                    //root
        if(t->left) 
            s += "(" + tree2str(t->left) + ")";   //left
        else if(t->right) //左为空，加括号注明其为空
            s+= "()";
        
        if(t->right) s+= "(" + tree2str(t->right) + ")"; //right
        return s;
    }
};
```
