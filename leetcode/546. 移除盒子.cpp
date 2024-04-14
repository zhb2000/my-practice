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
    int removeBoxes(const vector<int> &boxes)
    {
        int n = int(boxes.size());
        auto dp = vector(n, vector(n, vector<int>(n)));
        function<int(int, int, int)> f = [&](int l, int r, int k) {
            if (r < l)
                return 0;
            if (dp[l][r][k] != 0)
                return dp[l][r][k];
            int ans = f(l, r - 1, 0) + (k + 1) * (k + 1);
            for (int i = l; i < r; i++)
            {
                if (boxes[i] == boxes[r])
                {
                    int temp = f(l, i, k + 1) + f(i + 1, r - 1, 0);
                    ans = max(ans, temp);
                }
            }
            dp[l][r][k] = ans;
            return ans;
        };
        return f(0, n - 1, 0);
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    assert(sol()->removeBoxes({1, 3, 2, 2, 2, 3, 4, 3, 1}) == 23);
    return 0;
}
