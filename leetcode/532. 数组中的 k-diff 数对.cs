// 532. 数组中的 k-diff 数对
// https://leetcode.cn/problems/k-diff-pairs-in-an-array/

class Solution
{
    static Dictionary<T, int> MakeCounter<T>(IEnumerable<T> enumerable) where T : notnull
    {
        var counter = new Dictionary<T, int>();
        foreach (T x in enumerable)
        {
            counter.TryAdd(x, 0);
            counter[x]++;
        }
        return counter;
    }

    public int FindPairs(int[] nums, int k)
    {
        if (k == 0)
        {
            return MakeCounter(nums).Where(kv => kv.Value > 1).Count();
        }
        else
        {
            var set = nums.ToHashSet();
            int ans = 0;
            foreach (int x in set)
            {
                if (set.Contains(x - k))
                    ans++;
                if (set.Contains(x + k))
                    ans++;
            }
            return ans / 2;
        }
    }
}

class LeetCode
{
    public static void Main()
    {
        var solution = new Solution();
        Console.WriteLine(solution.FindPairs(new int[] { 3, 1, 4, 1, 5 }, 2));
        Console.WriteLine(solution.FindPairs(new int[] { 1, 2, 3, 4, 5 }, 1));
        Console.WriteLine(solution.FindPairs(new int[] { 1, 3, 1, 5, 4 }, 0));
    }
}
