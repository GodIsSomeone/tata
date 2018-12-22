输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）


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
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        bool bRet = false;
        //当Tree1和Tree2都不为零的时候，才进行比较。否则直接返回false
        if(pRoot1 != nullptr && pRoot2 != nullptr)
        {
          //如果找到了对应Tree2的根节点的点
            if(pRoot1->val == pRoot2->val)
            {
              //以这个根节点为为起点判断是否包含Tree2
                bRet = helper(pRoot1,pRoot2);
            }
            //如果找不到，那么就再去root的左儿子当作起点，去判断时候包含Tree2
            if(!bRet)
            {
                bRet = HasSubtree(pRoot1->left,pRoot2);
            }
            //如果还找不到，那么就再去root的右儿子当作起点，去判断时候包含Tree2
            if(!bRet)
            {
                bRet = HasSubtree(pRoot1->right,pRoot2);
            }
        }
 
        return bRet;
    }
     
    bool helper(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        //如果Tree2已经遍历完了都能对应的上，返回true
        if(pRoot2 == nullptr) return true;
        //如果Tree2还没有遍历完，Tree1却遍历完了。返回false
        if(pRoot1 == nullptr) return false;
         //如果其中有一个点没有对应上，返回false
        if(pRoot1->val != pRoot2->val)
        {
            return false;
        }
        //如果根节点对应的上，那么就分别去子节点里面匹配
        return helper(pRoot1->left,pRoot2->left) && helper(pRoot1->right,pRoot2->right);
    }
};

```
