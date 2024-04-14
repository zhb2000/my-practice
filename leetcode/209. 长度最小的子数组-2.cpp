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
    int minSubArrayLen(int target, const vector<int> &nums)
    {
        const int n = int(nums.size());
        int ans = 0;
        int sum = 0;
        int l = 0;
        int r = -1;
        while (true)
        {
            if (sum < target)
            {
                if (r + 1 < n)
                {
                    r++;
                    sum += nums[r];
                }
                else
                    break;
            }
            else // sum >= target
            {
                int current_ans = r - l + 1;
                if (ans == 0 || current_ans < ans)
                    ans = current_ans;
                sum -= nums[l];
                l++;
            }
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
    return 0;
}
