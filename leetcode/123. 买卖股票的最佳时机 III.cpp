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
        if (n < 2)
            return 0;
        int max_two_profit = 0;
        int max_price = 0;
        int max_one_profit = 0;
        array<int, 2> max_one_profits{};
        int max_price_profit = 0; // maximun of (price[i] + max_one_profit[i+1])
        for (int i = n - 1; i >= 0; i--)
        {
            int price = prices[i];
            int two_profit = max_price_profit - price;
            max_two_profit = max(max_two_profit, two_profit);

            int price_profit = price;
            if (i + 1 < n)
                price_profit += max_one_profits[(i + 1) % 2];
            max_price_profit = max(max_price_profit, price_profit);

            int one_profit = max_price - price;
            max_one_profit = max(max_one_profit, one_profit);
            max_one_profits[i % 2] = max_one_profit;
            max_price = max(max_price, price);
        }
        return max_two_profit;
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    vector<int> prices;
    prices = {3, 3, 5, 0, 0, 3, 1, 4};
    assert(sol()->maxProfit(prices) == 6);
    prices = {1, 2, 3, 4, 5};
    assert(sol()->maxProfit(prices) == 4);
    prices = {7, 6, 4, 3, 1};
    assert(sol()->maxProfit(prices) == 0);
    prices = {1};
    assert(sol()->maxProfit(prices) == 0);
}
