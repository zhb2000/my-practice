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
    int maximumTop(const vector<int> &nums, int k)
    {
        int n = int(nums.size());
        int ans = -1;
        for (int ops = 0; ops <= min(k, n - 1); ops++)
        {
            bool can;
            assert(k >= ops);
            if ((k - ops) % 2 == 0)
                can = true;
            else
            {
                if (k - ops != 1 && (ops + 1 < n || ops - 1 >= 0))
                    can = true;
                else
                    can = false;
            }
            if (can)
                ans = max(ans, nums[ops]);
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
    return 0;
}
