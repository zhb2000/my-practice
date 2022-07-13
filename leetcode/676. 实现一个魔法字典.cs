// 676. 实现一个魔法字典
// https://leetcode.cn/problems/implement-magic-dictionary/
// 字符串、哈希表
public class MagicDictionary
{
    readonly Dictionary<(string, string), List<string>> dict = new();

    public void BuildDict(string[] dictionary)
    {
        foreach (string s in dictionary)
        {
            foreach (var pair in PrefixSuffix(s))
            {
                if (!dict.ContainsKey(pair))
                    dict[pair] = new();
                dict[pair].Add(s);
            }
        }
    }

    public bool Search(string searchWord)
    {
        foreach (var pair in PrefixSuffix(searchWord))
            if (dict.ContainsKey(pair) && dict[pair].Any(s => s != searchWord))
                return true;
        return false;
    }

    static IEnumerable<(string, string)> PrefixSuffix(string s)
    {
        for (int i = 0; i < s.Length; i++)
            yield return (s[..i], s[(i + 1)..]);
    }
}

class LeetCode
{
    public static void Main()
    {
        var dict = new MagicDictionary();
        dict.BuildDict(new string[] { "hello", "hallo", "leetcode" });
        foreach (string s in new string[] { "hello", "hhllo", "hell", "leetcode" })
            Console.WriteLine(dict.Search(s));
    }
}
