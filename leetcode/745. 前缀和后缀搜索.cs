// 745. 前缀和后缀搜索
// https://leetcode.cn/problems/prefix-and-suffix-search/
// 在预处理阶段枚举每个单词所有可能的前缀和后缀，预处理时间复杂度 O(N * L^2)，每个查询的时间复杂度 O(L)。

public class WordFilter
{
    readonly Dictionary<(string, string), int> map = new();

    public WordFilter(string[] words)
    {
        foreach (var (index, word) in words.Enumerate())
        {
            int len = word.Length;
            for (int i = 1; i <= len; i++)
                for (int j = 1; j <= len; j++)
                    map[(word[..i], word[^j..])] = index;
        }
    }

    public int F(string prefix, string suffix)
        => map.GetValueOrDefault((prefix, suffix), -1);
}

static class Extension
{
    public static IEnumerable<(int, T)> Enumerate<T>(this IEnumerable<T> enumerable, int start = 0)
    {
        int index = start;
        foreach (T item in enumerable)
            yield return (index++, item);
    }
}
