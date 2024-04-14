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

// f[i][j] = f[i-1][j+1] + 1, if s[i] == s[j]
//         = max(f[i][j+1], f[i-1][j]), otherwise
// odd: 1 + f[i-1][i+1] * 2
// even: f[i][i+1] * 1
class Solution
{
public:
    int longestPalindromeSubseq(const string &s)
    {
        int n = int(s.length());
        auto fi = vector<int>(n);   // f[i][...]
        auto fi_1 = vector<int>(n); // f[i-1][...]
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = n - 1; j > i; j--)
            {
                if (s[i] == s[j])
                {
                    int fi_1j_1 = (j + 1 < n) ? fi_1[j + 1] : 0; // f[i-1][j+1]
                    fi[j] = fi_1j_1 + 1;
                }
                else
                {
                    int fij_1 = (j + 1 < n) ? fi[j + 1] : 0; // f[i][j+1]
                    int fi_1j = fi_1[j];                     // f[i-1][j]
                    fi[j] = max(fij_1, fi_1j);
                }
            }
            int fi_1i_1 = (i + 1 < n) ? fi_1[i + 1] : 0; // f[i-1][i+1]
            int odd_ans = 1 + fi_1i_1 * 2;
            int fii_1 = (i + 1 < n) ? fi[i + 1] : 0; // f[i][i+1]
            int even_ans = fii_1 * 2;
            ans = max({ans, odd_ans, even_ans});
            fi_1 = fi;
        }
        return ans;
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    assert(sol()->longestPalindromeSubseq("bbbab") == 4);
    assert(sol()->longestPalindromeSubseq("cbbd") == 2);
    return 0;
}
