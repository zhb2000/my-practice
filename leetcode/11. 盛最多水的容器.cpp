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

#include <span>
namespace rng = std::ranges;

class Solution
{
public:
    int maxArea(const vector<int> &height)
    {
        int ans = 0;
        int i = 0;
        int j = int(height.size()) - 1;
        while (i < j)
        {
            int temp = (j - i) * min(height[i], height[j]);
            ans = max(ans, temp);
            if (height[i] < height[j])
                i++;
            else
                j--;
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
    assert(sol()->maxArea({1, 8, 6, 2, 5, 4, 8, 3, 7}) == 49);
    assert(sol()->maxArea({1, 1}) == 1);
    return 0;
}
