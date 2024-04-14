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
    int lengthOfLongestSubstring(const string &s)
    {
        int n = int(s.length());
        int max_len = 0;
        int r = -1;
        unordered_set<char> window_set;
        for (int l = 0; l < n; l++)
        {
            // cout << "move l: " << l << endl;
            if (l > 0)
                window_set.erase(s[l - 1]);
            assert(r >= l - 1);
            while (r + 1 < n && !window_set.contains(s[r + 1]))
            {
                r++;
                // cout << "move r: " << r << endl;
                window_set.insert(s[r]);
            }
            int len = r - l + 1;
            max_len = max(max_len, len);
        }
        return max_len;
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
