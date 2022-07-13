// 1252. 奇数值单元格的数目
// https://leetcode.cn/problems/cells-with-odd-values-in-a-matrix/
// 思维题
// 只考虑出现奇数次的行/列，可以直接把答案算出来
public class Solution
{
    public int OddCells(int m, int n, int[][] indices)
    {
        var rows = indices
            .Select(p => p[0])
            .MakeCounter()
            .Where(kv => kv.Value % 2 == 1)
            .Count();
        var cols = indices
            .Select(p => p[1])
            .MakeCounter()
            .Where(kv => kv.Value % 2 == 1)
            .Count();
        return rows * n + cols * m - rows * cols * 2;
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
    public static void Main()
    {

    }
}
