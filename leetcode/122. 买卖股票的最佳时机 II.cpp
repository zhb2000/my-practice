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

#include <ranges>

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

#include <span>
namespace rng = std::ranges;
namespace vs = std::views;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        if (prices.size() < 2)
            return 0;
        int sum = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            int x = prices[i] - prices[i - 1];
            if (x > 0)
                sum += x;
        }
        return sum;
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    vector<int> prices;
    prices = {7, 1, 5, 3, 6, 4};
    assert(sol()->maxProfit(prices) == 7);
    prices = {1, 2, 3, 4, 5};
    assert(sol()->maxProfit(prices) == 4);
    prices = {7, 6, 4, 3, 1};
    assert(sol()->maxProfit(prices) == 0);
    return 0;
}
