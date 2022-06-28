// 522. 最长特殊序列 II
// https://leetcode.cn/problems/longest-uncommon-subsequence-ii/
// 暴力枚举子集
using System.Text;

public class Solution
{
    public int FindLUSlength(string[] strs)
    {
        return strs
            .Select(s => Subsequence(s))
            .SelectMany(s => s)
            .MakeCounter()
            .Where(kv => kv.Value == 1)
            .Select(kv => kv.Key.Length)
            .DefaultIfEmpty(-1)
            .Max();
    }

    static IEnumerable<string> Subsequence(string s)
    {
        int len = s.Length;
        var sb = new StringBuilder();
        for (int subset = 0; subset < (1 << len); subset++)
        {
            sb.Clear();
            for (int i = 0; i < len; i++)
                if ((subset & (1 << i)) != 0)
                    sb.Append(s[i]);
            yield return sb.ToString();
        }
    }
}

static class Extension
{
    public static Dictionary<T, int> MakeCounter<T>(this IEnumerable<T> enumerable)
        where T : notnull
    {
        var counter = new Dictionary<T, int>();
        foreach (T x in enumerable)
        {
            counter.TryAdd(x, 0);
            counter[x]++;
        }
        return counter;
    }
}

class LeetCode
{
    public static void Main() {}
}
