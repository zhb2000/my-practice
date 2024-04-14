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
        int l = 0;
        int r = 0;
        int current = nums[0];
        int last_ans_r = -1;
        while (true)
        {
            if (current < k)
            {
                r++;
                assert(l <= r);
                if (r < n)
                    current *= nums[r];
                if (current >= k || r == n) // [l, r-1] is ok but [l, r] is not ok
                {
                    int len = r - l; // [l, r-1]
                    if (len > 0)
                    {
                        // cout << "[" << l << ", " << r - 1 << "]\n";
                        int current_count = (1 + len) * len / 2;
                        if (l <= last_ans_r)
                        {
                            // cout << "l: " << l << ", last_ans_r: " << last_ans_r << endl;
                            int covered_len = last_ans_r - l + 1; // [l, last_ans_r]
                            current_count -= (1 + covered_len) * covered_len / 2;
                        }
                        count += current_count;
                        last_ans_r = r - 1;
                    }
                    if (r == n)
                        break;
                }
            }
            else
            {
                l++;
                current /= nums[l - 1];
            }
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
