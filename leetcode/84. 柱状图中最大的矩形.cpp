#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <deque>
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
    assert(sol()->largestRectangleArea({2, 1, 5, 6, 2, 3}) == 10);
    assert(sol()->largestRectangleArea({2, 4}) == 4);
    return 0;
}
