#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
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

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    os << '[';
    bool first = true;
    for (const T &x : v)
    {
        if (first)
            first = false;
        else
            os << ", ";
        os << x;
    }
    os << ']';
    return os;
}

#include <bit>
#include <ranges>
#include <span>
namespace rng = std::ranges;
namespace vs = std::views;
using ll = long long;
using ull = unsigned long long;

class Solution
{
public:
    string longestDupSubstring(const string &s)
    {
        constexpr ll BASE = 26 + 1;
        constexpr ll MOD = ll(1e9 + 3);
        int n = int(s.length());
        vector<ll> base_n = make_base_n<BASE, MOD>(n);
        vector<ll> hashes = make_hashes<BASE, MOD>(s);
        unordered_map<ll, vector<string_view>> values;
        string_view ans;
        auto exist_duplicate = [&](int len) {
            values.clear();
            if (len == 0)
                return true;
            for (int l = 0; l + len - 1 < n; l++)
            {
                ll hash = get_hash<MOD>(hashes, l, l + len - 1, base_n);
                auto sub = string_view(s.begin() + l, s.begin() + l + len);
                if (!values.contains(hash))
                    values[hash] = {sub};
                else
                {
                    for (string_view existed : values[hash])
                    {
                        if (sub == existed)
                        {
                            if (sub.length() > ans.length())
                                ans = sub;
                            return true;
                        }
                    }
                    values[hash].push_back(sub);
                }
            }
            return false;
        };
        int start = 0;
        int stop = n + 1;
        while (start < stop)
        {
            int len = start + (stop - start) / 2;
            if (exist_duplicate(len))
                start = len + 1;
            else
                stop = len;
        }
        return string(ans);
    }

    // 预处理出模 MOD 意义下 BASE 的所有次幂
    template <ll BASE, ll MOD>
    static vector<ll> make_base_n(int length)
    {
        vector<ll> base_n;
        base_n.push_back(1); // base^0 = 1
        for (int i = 1; i < length; i++)
            base_n.push_back(base_n[i - 1] * BASE % MOD);
        return base_n;
    }

    // 预处理出字符串的前缀哈希值
    template <ll BASE, ll MOD>
    static vector<ll> make_hashes(const string &s)
    {
        vector<ll> hashes;
        for (int i = 0; i < int(s.size()); i++)
        {
            ll hash;
            if (i == 0)
                hash = s[i] - 'a' + 1;
            else
                hash = (hashes[i - 1] * BASE + (s[i] - 'a' + 1)) % MOD;
            hashes.push_back(hash);
        }
        return hashes;
    }

    // 获取子串 [l, r] 的哈希值
    template <ll MOD>
    static ll get_hash(const vector<ll> &hashes, int l, int r, const vector<ll> &base_n)
    {
        if (l == 0)
            return hashes[r];
        int len = r - l + 1;
        ll hash = (hashes[r] - hashes[l - 1] * base_n[len] % MOD) % MOD;
        // C++ 中负数取模的结果为负数（例如 -10 % 3 = -1 而不是 2）
        // 需要手动变为正数
        if (hash < 0)
            hash += MOD;
        return hash;
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    return 0;
}
