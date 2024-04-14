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
    int canCompleteCircuit(const vector<int> &gas, const vector<int> &cost)
    {
        int n = int(gas.size());
        int start = 0;
        while (start < n)
        {
            int oil = 0;
            int i = start;
            bool can = true;
            for (int cnt = 1; cnt <= n; cnt++)
            {
                oil += gas[i] - cost[i]; // from i to i+1
                if (oil < 0)
                {
                    can = false;
                    break;
                }
                i++; // can reach, move i to i+1
                if (i >= n)
                    i -= n;
            }
            if (can)
            {
                assert(i == start);
                return start;
            }
            // start can reach i but cannot reach i+1
            if (i < start)
                break;
            start = i + 1;
        }
        return -1;
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    assert(sol()->canCompleteCircuit({2, 3, 4}, {3, 4, 3}) == -1);
    return 0;
}
