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
    vector<int> maxSlidingWindow(const vector<int> &nums, int k)
    {
        deque<int> q;
        // front --- back, decrease, front is the biggest
        auto enqueue = [&q, &nums](int r) {
            while (!q.empty() && nums[q.back()] < nums[r])
                q.pop_back();
            q.push_back(r);
        };
        auto dequeue = [&q, &nums](int l) {
            assert(!q.empty());
            if (q.front() == l)
                q.pop_front();
        };
        vector<int> ans;
        for (int i : vs::iota(0, k))
            enqueue(i);
        ans.push_back(nums[q.front()]);
        for (int i : vs::iota(k, int(nums.size())))
        {
            enqueue(i);
            dequeue(i - k);
            assert(!q.empty());
            ans.push_back(nums[q.front()]);
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
    assert(sol()->maxSlidingWindow({1, 3, -1, -3, 5, 3, 6, 7}, 3) == vector({3, 3, 5, 5, 6, 7}));
    assert(sol()->maxSlidingWindow({1}, 1) == vector({1}));
    return 0;
}
