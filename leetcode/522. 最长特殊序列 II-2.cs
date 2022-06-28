// 522. 最长特殊序列 II
// https://leetcode.cn/problems/longest-uncommon-subsequence-ii/
// 思维题、判断子序列、双指针
public class Solution
{
    public int FindLUSlength(string[] strs)
    {
        int maxLen = -1;
        foreach (var (i, s1) in strs.Enumerate())
        {
            bool special = strs
                .Enumerate()
                .Where(p => p.Item1 != i)
                .All(p => !IsSubsequence(s1, p.Item2));
            if (special)
                maxLen = Math.Max(maxLen, s1.Length);
        }
        return maxLen;
    }

    public static bool IsSubsequence(string s1, string s2)
    {
        int i = 0, j = 0;
        while (i < s1.Length && j < s2.Length)
        {
            if (s1[i] == s2[j])
                i++;
            j++;

        }
        return i == s1.Length;
    }
}

static class Extension
{
    public static IEnumerable<(int, T)> Enumerate<T>(this IEnumerable<T> enumerate, int start = 0)
    {
        int i = start;
        foreach (T x in enumerate)
            yield return (i++, x);
    }
}

class LeetCode
{
    public static void Main()
    {
        var sol = new Solution();
        Console.WriteLine(sol.FindLUSlength(new string[] { "aba", "cdc", "eae" }));
    }
}
