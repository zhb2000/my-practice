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

// f[i][j] = f[i-1][j-1] + 1, if s[i] == s[j]
//         = max(f[i-1][j], f[i][j-1]), otherwise
class Solution
{
public:
    int longestCommonSubsequence(const string &s1, const string &s2)
    {
        int n = int(s1.length());
        int m = int(s2.length());
        auto fi = vector<int>(m);   // f[i][...]
        auto fi_1 = vector<int>(m); // f[i-1][...]
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (s1[i] == s2[j])
                {
                    int fi_1j_1 = (i - 1 >= 0 && j - 1 >= 0) ? fi_1[j - 1] : 0; // f[i-1][j-1]
                    fi[j] = fi_1j_1 + 1;                                        // f[i][j] = f[i-1][j-1] + 1
                }
                else
                {
                    int fi_1j = (i - 1 >= 0) ? fi_1[j] : 0; // f[i-1][j]
                    int fij_1 = (j - 1 >= 0) ? fi[j - 1] : 0;   // f[i][j-1]
                    fi[j] = max(fi_1j, fij_1);
                }
            }
            fi_1 = fi; // clone to f[i-1][...]
        }
        return fi[m - 1]; // f[n-1][m-1]
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
