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
    int maximalRectangle(const vector<vector<char>> &matrix)
    {
        const int rows = int(matrix.size());
        const int cols = int(matrix[0].size());
        auto sums = vector<vector<int>>(rows, vector<int>(cols));
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                if (r > 0)
                    sums[r][c] = sums[r - 1][c] + matrix[r][c] - '0';
                else
                    sums[r][c] = matrix[r][c] - '0';
            }
        }
        int ans = 0;
        for (int r1 = 0; r1 < rows; r1++)
        {
            for (int r2 = r1; r2 < rows; r2++)
            {
                int height = r2 - r1 + 1;
                auto all_one = [=, &sums](int c) {
                    int sum = (r1 > 0) ? sums[r2][c] - sums[r1 - 1][c] : sums[r2][c];
                    return sum == height;
                };
                for (int c1 = 0; c1 < cols; c1++)
                {
                    if (!all_one(c1))
                        continue;
                    int c2 = c1 + 1;
                    for (c2 = c1 + 1; c2 < cols; c2++)
                        if (!all_one(c2))
                            break;
                    c2 -= 1;
                    int width = c2 - c1 + 1;
                    int temp_ans = height * width;
                    ans = max(ans, temp_ans);
                    c1 = c2;
                }
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
    vector<vector<char>> matrix;
    matrix = {{'1', '0', '1', '0', '0'},
              {'1', '0', '1', '1', '1'},
              {'1', '1', '1', '1', '1'},
              {'1', '0', '0', '1', '0'}};
    assert(sol()->maximalRectangle(matrix) == 6);
    matrix = {{'0'}};
    assert(sol()->maximalRectangle(matrix) == 0);
    matrix = {{'1'}};
    assert(sol()->maximalRectangle(matrix) == 1);
    return 0;
}
