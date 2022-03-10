// 395. 至少有 K 个重复字符的最长子串
// https://leetcode-cn.com/problems/longest-substring-with-at-least-k-repeating-characters/
// 分治
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <deque>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
public:
    static int longestSubstring(const string &s, int k)
    {
        return longest_substring(s, k);
    }

    static int longest_substring(string_view s, int k)
    {
        array<int, 26> cnt = {0};
        for (char ch : s)
            cnt[ch - 'a']++;
        int *p = find_if(cnt.begin(), cnt.end(),
                         [k](int c) { return 0 < c && c < k; });
        if (p == cnt.end())
            return int(s.length());
        // 选取一个出现次数在 0 到 k 之间的字母 delimiter
        // 答案必不包含 delimiter，因此答案必出现在被 delimiter 分割的子串之中，递归到子串中即可
        char delimiter = char(p - cnt.begin() + 'a');
        int max_len = 0;
        for (string_view sub : split(s, delimiter))
            max_len = max(max_len, longest_substring(sub, k));
        return max_len;
    }

    /// 把 s 切分为不含 delimiter 的子串
    static vector<string_view> split(string_view s, char delimiter)
    {
        auto is_delimiter = [=](char ch) { return ch == delimiter; };
        vector<string_view> substrings;
        auto start = find_if_not(s.begin(), s.end(), is_delimiter);
        // start is not a delimiter
        while (start != s.end())
        {
            auto stop = find_if(start, s.end(), is_delimiter);
            // stop is a delimiter or s.end()
            // [start, stop)
            substrings.emplace_back(start, stop - start);
            start = find_if_not(stop, s.end(), is_delimiter);
        }
        return substrings;
    }
};

int main()
{

    cout << Solution::longestSubstring("aaabb", 3) << endl;  // 3
    cout << Solution::longestSubstring("ababbc", 2) << endl; // 5

    return 0;
}
