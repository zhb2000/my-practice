// 199. 二叉树的右视图
// https://leetcode.cn/problems/binary-tree-right-side-view/
// 层序遍历、BFS
using System.Collections;

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

#nullable enable
public class Solution
{
    public IList<int> RightSideView(TreeNode? root)
    {
        var list = new List<int>();
        if (root == null)
            return list;
        var q = new Queue<(TreeNode, int)>();
        q.Enqueue((root, 0));
        int lastFloor = -1;
        while (q.Count > 0)
        {
            var (u, floor) = q.Dequeue();
            if (floor == lastFloor)
                list[^1] = u.val;
            else // floor > lastFloor
                list.Add(u.val);
            lastFloor = floor;
            if (u.left is not null)
                q.Enqueue((u.left, floor + 1));
            if (u.right is not null)
                q.Enqueue((u.right, floor + 1));
        }
        return list;
    }
}

class LeetCode
{
    public static void Main()
    {
    }
}
