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
    int maxProfit(int K, vector<int> &prices)
    {
        int n = int(prices.size());
        if (n < 2)
            return 0;
        // profit[i][k] = max_price_profit[i+1][k] - price[i], if buy at day i
        auto max_profits = vector(2, vector<int>(K + 1)); // int[2][K+1]
        // price_profit[i][k] = price[i] + max_profits[i+1][k-1], if sell at day i
        auto max_price_profits = vector<int>(K + 1);
        for (int i = n - 1; i >= 0; i--)
        {
            int price = prices[i];
            for (int k = 0; k <= K; k++)
            {
                int profit;       // profit[i][k]
                int price_profit; // price_profit[i][k]
                if (k == 0)
                {
                    profit = 0;
                    price_profit = price;
                }
                else
                {
                    profit = max_price_profits[k] - price;
                    price_profit = price + max_profits[(i + 1) % 2][k - 1];
                }
                max_profits[i % 2][k] = max(max_profits[(i + 1) % 2][k], profit);
                max_price_profits[k] = max(max_price_profits[k], price_profit);
                // cout << "profit[" << i << "][" << k << "]: " << profit << ", ";
                // cout << "price_profit[" << i << "][" << k << "]: " << price_profit << endl;
            }
        }
        return max_profits[0][K];
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    vector<int> prices;
    prices = {2, 4, 1};
    assert(sol()->maxProfit(2, prices) == 2);
    prices = {3, 2, 6, 5, 0, 3};
    assert(sol()->maxProfit(2, prices) == 7);

    // prices = {3, 5, 0, 3, 1, 4};
    // cout << sol()->maxProfit(2, prices) << endl;

    prices = {3, 3, 5, 0, 0, 3, 1, 4};
    assert(sol()->maxProfit(2, prices) == 6);
    return 0;
}
