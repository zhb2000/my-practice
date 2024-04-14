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
    int subarraySum(const vector<int> &nums, int k)
    {
        int n = int(nums.size());
        auto prefix_sum = vector<int>(n);
        unordered_map<int, int> counter;
        int ans = 0;
        counter[0] = 1;
        for (int i = 0; i < n; i++)
        {
            prefix_sum[i] = (i > 0) ? prefix_sum[i - 1] + nums[i] : nums[i];
            int expected = prefix_sum[i] - k; // prefix_sum[i] - expected = k
            if (counter.contains(expected))
                ans += counter[expected];
            if (!counter.contains(prefix_sum[i]))
                counter[prefix_sum[i]] = 0;
            counter[prefix_sum[i]]++;
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
    assert(sol()->subarraySum({1, 2, 3}, 3));
    return 0;
}
