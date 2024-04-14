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
    int numSubarrayProductLessThanK(const vector<int> &nums, int k)
    {
        if (k <= 1)
            return 0;
        int n = int(nums.size());
        int count = 0;
        int l = 0; // [l, r] is the window
        int window_value = 1;
        for(int r = 0; r < n; r++)
        {
            window_value *= nums[r];
            while(l <= r && window_value >= k)
            {
                window_value /= nums[l];
                l++;
            }
            int len = r - l + 1; // [l, r] is ok
            count += len;
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
    cout << sol()->numSubarrayProductLessThanK({10, 5, 2, 6, 100}, 100) << endl;
    assert(sol()->numSubarrayProductLessThanK({10, 5, 2, 6}, 100) == 8);
    return 0;
}
