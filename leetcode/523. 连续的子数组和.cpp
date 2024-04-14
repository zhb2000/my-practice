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
    bool checkSubarraySum(const vector<int> &nums, int k)
    {
        int n = int(nums.size());
        ll last_prefix_sum = 0;
        unordered_map<ll, int> negsums;
        negsums[0] = -1;
        for (int i = 0; i < n; i++)
        {
            ll prefix_sum = (last_prefix_sum + nums[i] % k) % k;
            ll wanted = (prefix_sum != 0) ? k - prefix_sum : 0;
            if (negsums.contains(wanted) && i - negsums[wanted] >= 2)
                return true;
            ll neg_prefix_sum = (-prefix_sum + k) % k;
            if (!negsums.contains(neg_prefix_sum))
                negsums[neg_prefix_sum] = i;
            last_prefix_sum = prefix_sum;
        }
        return false;
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
