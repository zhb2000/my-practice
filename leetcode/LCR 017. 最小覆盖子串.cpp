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
    string minWindow(const string &s, const string &t)
    {
        unordered_map<char, int> t_counter;
        for(char ch : t)
        {
            if(!t_counter.contains(ch))
                t_counter[ch] = 0;
            t_counter[ch]++;
        }
        string_view ans;
        const int n = int(s.length());
        int l = 0, r = -1;
        unordered_map<char, int> counter;
        unordered_set<char> still_need(t.begin(), t.end());
        while (true)
        {
            if (!still_need.empty())
            {
                r++;
                assert(l <= r);
                if (r >= n)
                {
                    assert(r == n);
                    break;
                }
                if (t_counter.contains(s[r]))
                {
                    if(!counter.contains(s[r]))
                        counter[s[r]] = 0;
                    counter[s[r]]++;
                    if(counter[s[r]] >= t_counter[s[r]])
                        still_need.erase(s[r]);
                }
            }
            else
            {
                assert(l <= r);
                if (ans.empty() || r - l + 1 < int(ans.length()))
                    ans = string_view(s.begin() + l, s.begin() + r + 1);
                if (counter.contains(s[l]))
                {
                    counter[s[l]]--;
                    if(counter[s[l]] < t_counter[s[l]])
                        still_need.insert(s[l]);
                }
                l++;
            }
        }
        return std::string(ans);
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    assert(sol()->minWindow("ADOBECODEBANC", "ABC") == "BANC");
    assert(sol()->minWindow("a", "a") == "a");
    assert(sol()->minWindow("a", "aa") == "");
    return 0;
}
