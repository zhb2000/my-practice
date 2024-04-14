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
        int l = 0;
        int r = -1;
        int ans = 0;
        unordered_set<char> current_set;
        char duplicate = '\0';
        while (true)
        {
            if (duplicate == '\0')
            {
                r++;
                if (r >= n)
                    break;
                if (current_set.contains(s[r]))
                    duplicate = s[r];
                else
                {
                    current_set.insert(s[r]);
                    int current_ans = r - l + 1;
                    ans = max(ans, current_ans);
                }
            }
            else
            {
                l++;
                if (duplicate == s[l - 1])
                    duplicate = '\0';
                else
                    current_set.erase(s[l - 1]);
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
