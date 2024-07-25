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
    // a + b = sum
    // a - b = target
    // 2b = sum - target
    // b = (sum - target) / 2
    int findTargetSumWays(const vector<int> &nums, int target)
    {
        int n = int(nums.size());
        int sum = std::accumulate(nums.begin(), nums.end(), int(0));
        if (sum - target < 0)
            return 0;
        if ((sum - target) % 2 != 0)
            return 0;
        int want = (sum - target) / 2;
        if (want < 0 || want > sum)
            return 0;
        // dp[i][b]: nums[0..i], solutions of select elem to sum as b
        // dp[n][sum+3]
        auto dp = vector<vector<int>>(2, vector<int>(sum + 3, 0));
        for (int i = 0; i < n; i++)
        {
            for (int b = 0; b <= sum; b++)
            {
                int a1; // not select nums[i]
                int a2; // select nums[i]
                if (i > 0)
                {
                    a1 = dp[(i - 1) % 2][b];
                    // 注意 DP 的边界条件，b - nums[i] 不要越界
                    a2 = (b - nums[i] >= 0) ? dp[(i - 1) % 2][b - nums[i]] : 0;
                }
                else
                {
                    // 注意 DP 的边界条件，dp[-1][0] = 1
                    a1 = (b == 0) ? 1 : 0;
                    a2 = (b - nums[i] == 0) ? 1 : 0;
                }
                dp[i % 2][b] = a1 + a2;
            }
        }
        int ans = dp[(n - 1) % 2][want];
        return ans;
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    assert(sol()->findTargetSumWays({100, 100}, -400) == 0);
    assert(sol()->findTargetSumWays({1, 1, 1, 1, 1}, 3) == 5);
    assert(sol()->findTargetSumWays({1, 0}, 1) == 2);
    return 0;
}
