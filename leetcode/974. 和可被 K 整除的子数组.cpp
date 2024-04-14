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
    int subarraysDivByK(vector<int> &nums, int k)
    {
        int n = int(nums.size());
        int last_prefix_sum = 0;
        unordered_map<int, int> negsum_counter;
        negsum_counter[0] = 1;
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            int prefix_sum = (last_prefix_sum + nums[i] % k) % k;
            if (prefix_sum < 0)
                prefix_sum += k;
            int wanted = (prefix_sum != 0) ? k - prefix_sum : 0;
            if (negsum_counter.contains(wanted))
                count += negsum_counter[wanted];
            int neg_prefix_sum = (-prefix_sum + k) % k;
            if (!negsum_counter.contains(neg_prefix_sum))
                negsum_counter[neg_prefix_sum] = 0;
            negsum_counter[neg_prefix_sum]++;
            last_prefix_sum = prefix_sum;
        }
        return count;
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
