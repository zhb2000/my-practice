// 380. O(1) 时间插入、删除和获取随机元素
// https://leetcode.cn/problems/insert-delete-getrandom-o1/
// 设计题
// swap 到末尾再 pop back 来删除
public class RandomizedSet
{
    readonly Random random = new();
    readonly List<int> list = new();
    readonly Dictionary<int, int> num2index = new();

    public bool Insert(int val)
    {
        if (num2index.ContainsKey(val))
            return false;
        list.Add(val);
        num2index[val] = list.Count - 1;
        return true;
    }

    public bool Remove(int val)
    {
        if (!num2index.ContainsKey(val))
            return false;
        int i = num2index[val];
        if (i == list.Count - 1)
        {
            list.RemoveAt(list.Count - 1);
            num2index.Remove(val);
        }
        else
        {
            list[i] = list[^1];
            list.RemoveAt(list.Count - 1); // pop back
            num2index.Remove(val);
            num2index[list[i]] = i;
        }
        return true;
    }

    public int GetRandom() => list[random.Next(0, list.Count)];
}

class LeetCode
{
    public static void Main()
    {
        var set = new RandomizedSet();
        set.Insert(1);
        set.Remove(2);
        set.Insert(2);
        set.GetRandom();
    }
}
