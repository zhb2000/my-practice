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

using std::vector, std::string, std::unordered_map, std::unordered_set, std::map, std::set,
    std::cin, std::cout, std::endl, std::make_unique;

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

class Solution
{
public:

    int change(int amount, std::vector<int> &coins)
    {
        auto dp = vector<int>(amount + 1);
        dp[0] = 1;
        for(int coin : coins)
            for (int m = coin; m <= amount; m++)
                dp[m] += dp[m - coin];
        return dp[amount];
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    vector<int> coins;
    coins = {1, 2, 5};
    assert(sol()->change(5, coins) == 4);
    coins = {2};
    assert(sol()->change(3, coins) == 0);
    coins = {10};
    assert(sol()->change(10, coins) == 1);

    coins = {3, 5, 7, 8, 9, 10, 11};
    cout << sol()->change(500, coins) << endl;
    return 0;
}
