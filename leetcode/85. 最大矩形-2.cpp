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
        auto heights = vector<int>(cols);
        int ans = 0;
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                if (matrix[r][c] == '0')
                    heights[c] = 0;
                else
                    heights[c] += 1;
            }
            int temp_ans = largestRectangleArea(heights);
            ans = max(ans, temp_ans);
        }
        return ans;
    }

    int largestRectangleArea(const vector<int> &heights)
    {
        int n = int(heights.size());
        auto rights = vector<int>(n);
        stack<int, vector<int>> st;
        for (int i = 0; i < n; i++)
        {
            while (!st.empty() && heights[st.top()] > heights[i])
            {
                int j = st.top();
                st.pop();
                rights[j] = i - 1;
            }
            st.push(i);
        }
        while (!st.empty())
        {
            int j = st.top();
            st.pop();
            rights[j] = n - 1;
        }
        auto lefts = vector<int>(n);
        for (int i = n - 1; i >= 0; i--)
        {
            while (!st.empty() && heights[st.top()] > heights[i])
            {
                int j = st.top();
                st.pop();
                lefts[j] = i + 1;
            }
            st.push(i);
        }
        while (!st.empty())
        {
            int j = st.top();
            st.pop();
            lefts[j] = 0;
        }
        int ans = 0;
        for (int i = 0; i < n; i++)
            ans = max(ans, (rights[i] - lefts[i] + 1) * heights[i]);
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
