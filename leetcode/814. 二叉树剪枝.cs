// 814. 二叉树剪枝
// https://leetcode.cn/problems/binary-tree-pruning/
// 递归、DFS
public class TreeNode
{
    public int val;
    public TreeNode? left;
    public TreeNode? right;
    public TreeNode(int val = 0, TreeNode? left = null, TreeNode? right = null)
    {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

public class Solution
{
    public TreeNode? PruneTree(TreeNode? root)
    {
        if (root is null)
            return null;
        root.left = PruneTree(root.left);
        root.right = PruneTree(root.right);
        return (root.val == 0 && root.left is null && root.right is null)
            ? null : root;
    }
}

class LeetCode
{
    public static void Main()
    {
    }
}
