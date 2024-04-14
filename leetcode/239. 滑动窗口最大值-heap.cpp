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
        priority_queue<int> heap;
        unordered_map<int, int> counter;
        vector<int> ans;
        for (int i = 0; i < k; i++)
        {
            heap.push(nums[i]);
            if (!counter.contains(nums[i]))
                counter[nums[i]] = 0;
            counter[nums[i]]++;
        }
        ans.push_back(heap.top());
        for (int l = 1, r = 1 + k - 1; r < int(nums.size()); l++, r++)
        {
            assert(counter.contains(nums[l - 1]));
            counter[nums[l - 1]]--;
            if(!counter.contains(nums[r]))
                counter[nums[r]] = 0;
            counter[nums[r]]++;
            heap.push(nums[r]);
            while (counter[heap.top()] == 0)
                heap.pop();
            ans.push_back(heap.top());
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
