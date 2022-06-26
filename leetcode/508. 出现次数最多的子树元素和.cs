// 508. 出现次数最多的子树元素和
// https://leetcode.cn/problems/most-frequent-subtree-sum/
// DFS

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
    static int Dfs(TreeNode u, List<int> sums)
    {
        int sum = u.val;
        if (u.left != null)
            sum += Dfs(u.left, sums);
        if (u.right != null)
            sum += Dfs(u.right, sums);
        sums.Add(sum);
        return sum;
    }

    static Dictionary<T, int> MakeCounter<T>(IEnumerable<T> enumerable) where T : notnull
    {
        var counter = new Dictionary<T, int>();
        foreach (T item in enumerable)
        {
            counter.TryAdd(item, 0);
            counter[item]++;
        }
        return counter;
    }

    public int[] FindFrequentTreeSum(TreeNode root)
    {
        var sums = new List<int>();
        Dfs(root, sums);
        Dictionary<int, int> counter = MakeCounter(sums);
        int cnt = counter.Values.Max();
        return counter
            .Where(kv => kv.Value == cnt)
            .Select(kv => kv.Key)
            .ToArray();
    }
}
