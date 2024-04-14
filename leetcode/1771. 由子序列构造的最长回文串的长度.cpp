// region
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

// f[i][j] = f[i+1][j-1] + 2, if s[i] == s[j]
//         = max(f[i+1][j], f[i][j-1]), otherwise
class Solution
{
public:
    int longestPalindrome(const string &word1, const string &word2)
    {
        int n1 = int(word1.length());
        int n2 = int(word2.length());
        int n = n1 + n2;
        string s = word1 + word2;
        auto f = vector(n, vector<int>(n));
        auto g = vector(n, vector<int>(n));
        for (int i = 0; i < n; i++)
        {
            f[i][i] = 1;
            g[i][i] = f[i][i];
        }
        for (int i = 0; i + 1 < n; i++)
        {
            if (s[i] == s[i + 1])
            {
                f[i][i + 1] = 2;
                g[i][i + 1] = f[i][i + 1];
            }
            else
                f[i][i + 1] = 1;
        }
        for (int len = 3; len <= n; len++)
        {
            for (int i = 0; i + len - 1 < n; i++)
            {
                int j = i + len - 1;
                if (s[i] == s[j])
                {
                    f[i][j] = f[i + 1][j - 1] + 2;
                    g[i][j] = f[i][j];
                }
                else
                    f[i][j] = max(f[i + 1][j], f[i][j - 1]);
            }
        }
        int ans = 0;
        for (int i = 0; i < n1; i++)
            for (int j = n1; j < n; j++)
            {
                //                cout << format("g[{}][{}] = {}", i, j, g[i][j]) << endl;
                ans = max(ans, g[i][j]);
            }
        //        cout << f << endl;
        //        cout << g << endl;
        return ans;
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    assert(sol()->longestPalindrome("cfe", "ef") == 4);
    assert(sol()->longestPalindrome("rhuzwqohquamvsz", "kvunbxje") == 7);
    return 0;
}
