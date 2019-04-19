#### 最短深度    

递归解决，先判断返回条件，然后递归

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
    int minDepth(TreeNode* root) {
        int length = 0;
        if (root == NULL)
        {
            return length;
        }
        if (root != NULL && (root->left == NULL && root->right == NULL))
        {
            return 1;
        }
        if (root->left == NULL)
        {
            return 1 + minDepth(root->right);
        }
        else if (root->right == NULL)
        {
            return 1 + minDepth(root->left);
        }
        else
        {
            return 1 + min(minDepth(root->right), minDepth(root->left));
        }
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
     TreeNode left(2);
     TreeNode right(3);
     root->left = &left;
     root->right = &right;
    cout << Solution().minDepth(root) << endl;
    return 0;
}
```
