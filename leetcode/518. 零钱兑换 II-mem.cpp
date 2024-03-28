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
    map<std::pair<int, int>, int> mem;

    int change(int amount, std::vector<int> &coins)
    {
        mem.clear();
        int ans = f(amount, coins);
        return ans;
    }

    int f(int amount, std::span<int> coins)
    {
        if (coins.empty())
            return amount == 0 ? 1 : 0;
        auto p = std::make_pair(amount, int(coins.size()));
        if (mem.contains(p))
            return mem[p];
        int last = coins.back();
        int ans = 0;
        for (int used = 0; used <= amount; used += last)
        {
            ans += f(amount - used, coins.first(coins.size() - 1));
        }
        mem[p] = ans;
        return ans;
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
