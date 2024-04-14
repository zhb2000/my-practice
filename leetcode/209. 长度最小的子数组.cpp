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
    int minSubArrayLen(int target, const vector<int> &nums)
    {
        const int n = int(nums.size());
        int min_len = 0;
        int r = -1;
        int window_value = 0;
        for (int l = 0; l < n; l++)
        {
            if (l > 0)
                window_value -= nums[l - 1];
            assert(r >= l - 1);
            while (r + 1 < n && window_value < target)
            {
                r++;
                window_value += nums[r];
            }
            if (window_value >= target)
            {
                int len = r - l + 1;
                if (min_len == 0 || len < min_len)
                    min_len = len;
            }
        }
        return min_len;
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
