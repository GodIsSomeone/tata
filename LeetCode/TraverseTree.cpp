原题链接: http://oj.leetcode.com/problems/binary-tree-inorder-traversal/ 
通常，实现二叉树的遍历有两个常用的方法：一是用递归，二是使用栈实现的迭代方法。下面分别介绍。
递归应该最常用的算法，相信大家都了解，算法的时间复杂度是O(n), 而空间复杂度则是递归栈的大小，即O(logn)。代码如下： 

public ArrayList<Integer> inorderTraversal(TreeNode root) {  
    ArrayList<Integer> res = new ArrayList<Integer>();  
    helper(root, res);  
    return res;  
}  
private void helper(TreeNode root, ArrayList<Integer> res)  
{  
    if(root == null)  
        return;  
    helper(root.left,res);  
    res.add(root.val);  
    helper(root.right,res);  
}  



接下来是迭代的做法，其实就是用一个栈来模拟递归的过程。所以算法时间复杂度也是O(n)，空间复杂度是栈的大小O(logn)。
过程中维护一个node表示当前走到的结点（不是中序遍历的那个结点），实现的代码如下：

public ArrayList<Integer> inorderTraversal(TreeNode root) {  
    ArrayList<Integer> res = new ArrayList<Integer>();  
    LinkedList<TreeNode> stack = new LinkedList<TreeNode>();  
    while(root!=null || !stack.isEmpty())  
    {  
        if(root!=null)  
        {  
            stack.push(root);  
            root = root.left;  
        }  
        else  
        {  
            root = stack.pop();  
            res.add(root.val);  
            root = root.right;  
        }  
    }  
    return res;  
}  

原题链接: http://oj.leetcode.com/problems/binary-tree-preorder-traversal/ 
跟Binary Tree Inorder Traversal一样，二叉树的先序遍历我们仍然介绍三种方法，第一种是递归，第二种是迭代方法，第三种是用线索二叉树。
递归是最简单的方法，算法的时间复杂度是O(n), 而空间复杂度则是递归栈的大小，即O(logn)。代码如下：

public ArrayList<Integer> preorderTraversal(TreeNode root) {  
    ArrayList<Integer> res = new ArrayList<Integer>();  
    helper(root, res);  
    return res;  
}  
private void helper(TreeNode root, ArrayList<Integer> res)  
{  
    if(root == null)  
        return;  
    res.add(root.val);  
    helper(root.left,res);  
    helper(root.right,res);  
}  

接下来是迭代的做法，其实就是用一个栈来模拟递归的过程。所以算法时间复杂度也是O(n)，空间复杂度是栈的大小O(logn)。实现的代码如下:

public ArrayList<Integer> preorderTraversal(TreeNode root) {  
    ArrayList<Integer> res = new ArrayList<Integer>();  
    if(root == null)  
        return res;  
    LinkedList<TreeNode> stack = new LinkedList<TreeNode>();  
    while(root!=null || !stack.isEmpty())  
    {  
        if(root!=null)  
        {  
            stack.push(root);  
            res.add(root.val);  
            root = root.left;  
        }  
        else  
        {  
            root = stack.pop();  
            root = root.right;  
        }  
    }  
    return res;  
}  

原题链接: http://oj.leetcode.com/problems/binary-tree-postorder-traversal/ 
跟Binary Tree Inorder Traversal以及Binary Tree Preorder Traversal一样，二叉树的后序遍历我们还是介绍三种方法，第一种是递归，第二种是迭代方法，第三种是用线索二叉树。 
递归还是那么简单，算法的时间复杂度是O(n), 而空间复杂度则是递归栈的大小，即O(logn)。代码如下：

public ArrayList<Integer> postorderTraversal(TreeNode root) {  
    ArrayList<Integer> res = new ArrayList<Integer>();  
    helper(root, res);  
    return res;  
}  
private void helper(TreeNode root, ArrayList<Integer> res)  
{  
    if(root == null)  
        return;  
    helper(root.left,res);  
    helper(root.right,res);  
    res.add(root.val);  
}  

后来再看wiki的时候发现有跟Binary Tree Inorder Traversal和Binary Tree Preorder Traversal非常类似的解法，容易统一进行记忆，思路可以参考其他两种，区别是最下面在弹栈的时候需要分情况一下：
1）如果当前栈顶元素的右结点存在并且还没访问过（也就是右结点不等于上一个访问结点），那么就把当前结点移到右结点继续循环；
2）如果栈顶元素右结点是空或者已经访问过，那么说明栈顶元素的左右子树都访问完毕，应该访问自己继续回溯了。
下面列举一下代码：

public List<Integer> postorderTraversal(TreeNode root) {  
    List<Integer> res = new ArrayList<Integer>();  
    if(root == null)  
    {  
        return res;  
    }  
    LinkedList<TreeNode> stack = new LinkedList<TreeNode>();  
    TreeNode pre = null;  
    while(root != null || !stack.isEmpty())  
    {  
        if(root!=null)  
        {  
            stack.push(root);  
            root = root.left;  
        }  
        else  
        {  
            TreeNode peekNode = stack.peek();  
            if(peekNode.right!=null && pre != peekNode.right)  
            {  
                root = peekNode.right;  
            }  
            else  
            {  
                stack.pop();  
                res.add(peekNode.val);  
                pre = peekNode;  
            }  
        }  
    }  
    return res;  
}  

还有一种所谓的Morris遍历方法，没看。不过上述几个办法已经让我学习到了很多


    void Mirror(TreeNode *pRoot) {
        if(pRoot == nullptr) return;
        TreeNode *tmp = pRoot->left;
        pRoot->left = pRoot->right;
        pRoot->right = tmp;
        Mirror(pRoot->left);
        Mirror(pRoot->right);
        
    }
