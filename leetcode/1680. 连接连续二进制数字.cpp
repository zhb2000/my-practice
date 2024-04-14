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
    // x = log2(num), 2^x <= num
    static int log2(ull num)
    {
        constexpr int ull_bits = sizeof(ull) * 8;
        return ull_bits - std::countl_zero(num);
    }

    int concatenatedBinary(int n)
    {
        constexpr int MOD = int(1e9) + 7;
        ull ans = 0;
        ull m = 1;
        for (ull num = n; num >= 1; num--)
        {
            ans = (ans + num * m % MOD) % MOD;
            m = m * (ull(1) << log2(num)) % MOD;
        }
        return int(ans % MOD);
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    assert(sol()->concatenatedBinary(1) == 1);
    // cout << sol()->concatenatedBinary(3) << endl;
    assert(sol()->concatenatedBinary(3) == 27);
    assert(sol()->concatenatedBinary(12) == 505379714);
    return 0;
}
