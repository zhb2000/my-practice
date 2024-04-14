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
    int findLength(const vector<int> &nums1, const vector<int> &nums2)
    {
        int n = int(nums1.size());
        int m = int(nums2.size());
        auto dp = vector(n, vector<int>(m)); // int[n][m]
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int previous = (i > 0 && j > 0) ? dp[i - 1][j - 1] : 0;
                int current = (nums1[i] == nums2[j]) ? previous + 1 : 0;
                dp[i][j] = current;
                ans = max(ans, current);
            }
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
    assert(sol()->findLength({1, 2, 3, 2, 1}, {3, 2, 1, 4, 7}) == 3);
    assert(sol()->findLength({0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}) == 5);
    assert(sol()->findLength({0, 1, 1, 1, 1}, {1, 0, 1, 0, 1}) == 2);
    return 0;
}
