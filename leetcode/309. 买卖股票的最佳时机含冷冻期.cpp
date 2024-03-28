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

#include <ranges>
#include <span>
namespace rng = std::ranges;
namespace vs = std::views;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = int(prices.size());
        int ans = 0;
        auto max_profits = vector<int>(n);
        int max_price_profit = 0; // maximun of (price[i] + max_profits[i+2])
        for (int i = n - 1; i >= 0; i--)
        {
            int price = prices[i];
            int profit = max_price_profit - price;
            ans = max(ans, profit);
            max_profits[i] = ans;
            int price_profit = price;
            if (i + 2 < n)
                price_profit += max_profits[i + 2];
            max_price_profit = max(max_price_profit, price_profit);
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
    vector<int> prices;
    prices = {1, 2, 3, 0, 2};
    assert(sol()->maxProfit(prices) == 3);
    prices = {};
    assert(sol()->maxProfit(prices) == 0);
    prices = {1, 7, 2, 4};
    assert(sol()->maxProfit(prices) == 6);
    prices = {6, 1, 6, 4, 3, 0, 2};
    assert(sol()->maxProfit(prices) == 7);
    return 0;
}
