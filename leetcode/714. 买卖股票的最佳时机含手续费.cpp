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
    int maxProfit(vector<int> &prices, int fee)
    {
        int n = int(prices.size());
        if (n == 1)
            return 0;
        int ans = 0;
        auto max_profits = vector<int>(n); // max_profits[i]: max profit we can get from day i to last day
        int max_price_profit = 0; // maximun of (price[i] + max_profits[i+1])
        for(int i = n - 1; i >= 0; i--)
        {
            int price = prices[i];
            int profit = max_price_profit - price - fee;
            ans = max(ans, profit);
            max_profits[i] = ans;
            int price_profit = price;
            if (i + 1 < n)
                price_profit += max_profits[i + 1];
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
    prices = {1, 3, 2, 8, 4, 9};
    assert(sol()->maxProfit(prices, 2) == 8);
    prices = {1, 3, 7, 5, 10, 3};
    assert(sol()->maxProfit(prices, 3) == 6);
    return 0;
}
