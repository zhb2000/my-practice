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
        int ans = 0;
        int future_max = 0;
        for (int price : vs::reverse(prices))
        {
            int profit = future_max - price;
            ans = max(ans, profit);
            future_max = max(future_max, price);
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
    prices = {7, 1, 5, 3, 6, 4};
    assert(sol()->maxProfit(prices) == 5);
    prices = {7, 6, 4, 3, 1};
    assert(sol()->maxProfit(prices) == 0);
    return 0;
}
