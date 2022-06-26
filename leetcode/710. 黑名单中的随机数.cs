# 710. 黑名单中的随机数
# https://leetcode.cn/problems/random-pick-with-blacklist/
public class Solution
{
    readonly int whiteRange;
    readonly Random random = new();
    readonly Dictionary<int, int> map;

    public Solution(int n, int[] blacklist)
    {
        whiteRange = n - blacklist.Length;
        var blackset = blacklist.ToHashSet();
        var blackInRange = blacklist
            .Where(x => x < whiteRange);
        //var blackInRange = Range(0, whiteRange)
        //    .Where(blackset.Contains);
        var whiteNotInRange = Range(whiteRange, n)
            .Where(x => !blackset.Contains(x));
        map = blackInRange
            .Zip(whiteNotInRange)
            .ToDictionary(p => p.First, p => p.Second);
    }

    public int Pick()
    {
        int x = random.Next(0, whiteRange);
        return map.GetValueOrDefault(x, x);
    }

    static IEnumerable<int> Range(int start, int stop)
    {
        for (int i = start; i < stop; i++)
            yield return i;
    }
}

class LeetCode
{
    public static void Main()
    {
        var sol = new Solution(2, Array.Empty<int>());
        for (int c = 1; c < 10; c++)
            Console.WriteLine(sol.Pick());
    }
}
