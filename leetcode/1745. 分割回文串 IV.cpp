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
    bool checkPartitioning(const string &s)
    {
        int n = int(s.length());
        auto is_palindromic = vector(n, vector<bool>(n));
        for (int mid = 0; mid < n; mid++)
        {
            for (int l = mid, r = mid; 0 <= l && r < n; l--, r++)
            {
                if (s[l] == s[r])
                    is_palindromic[l][r] = true;
                else
                    break;
            }
            for (int l = mid, r = mid + 1; 0 <= l && r < n; l--, r++)
            {
                if (s[l] == s[r])
                    is_palindromic[l][r] = true;
                else
                    break;
            }
        }
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j + 1 < n; j++)
                if (is_palindromic[0][i] && is_palindromic[i + 1][j] && is_palindromic[j + 1][n - 1])
                    return true;
        return false;
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    assert(sol()->checkPartitioning("abcbdd"));
    assert(!sol()->checkPartitioning("bcbddxy"));
    return 0;
}
