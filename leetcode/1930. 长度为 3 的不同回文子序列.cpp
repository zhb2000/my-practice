// region header
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

#include <format>

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

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T>> &matrix)
{
    os << '[';
    bool first_row = true;
    for (const std::vector<T> &row : matrix)
    {
        if (first_row)
            first_row = false;
        else
            os << ",\n ";
        os << '[';
        bool first_col = true;
        for (const T &val : row)
        {
            if (first_col)
                first_col = false;
            else
                os << ", ";
            os << val;
        }
        os << ']';
    }
    os << ']';
    return os;
}
// endregion

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
    int countPalindromicSubsequence(const string &s)
    {
        constexpr int CHARSET = 26;
        int n = int(s.length());
        auto prefix_sum = vector(CHARSET, vector<int>(n));
        for (int c = 0; c < CHARSET; c++)
            for (int i = 0; i < n; i++)
                prefix_sum[c][i] = ((i - 1 >= 0) ? prefix_sum[c][i - 1] : 0) + int(s[i] - 'a' == c);
        unordered_set<ll> ans_set;
        for (int i = 1; i + 1 < n; i++)
        {
            int c = s[i] - 'a';
            for (int c1 = 0; c1 < CHARSET; c1++)
            {
                bool left_has_c1 = prefix_sum[c1][i - 1] > 0;
                bool right_has_c1 = prefix_sum[c1][n - 1] - prefix_sum[c1][i] > 0;
                if (left_has_c1 && right_has_c1)
                {
                    ll value = ll(c1) + ll(c) * CHARSET + ll(c1) * CHARSET * CHARSET;
                    ans_set.insert(value);
                    // cout << char(c1 + 'a') << char(c + 'a') << char(c1 + 'a') << endl;
                }
            }
        }
        return int(ans_set.size());
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    assert(sol()->countPalindromicSubsequence("aabca") == 3);
    return 0;
}
