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
    vector<int> partitionLabels(string s)
    {
        int n = int(s.length());
        int last_pos[26];
        for (int i = 0; i < n; i++)
            last_pos[s[i] - 'a'] = i;
        vector<int> ans;
        int left_i = 0;
        int right_i = last_pos[s[0] - 'a'];
        for (int i = 1; i < n; i++)
        {
            if (i > right_i)
            {
                ans.push_back(right_i - left_i + 1);
                left_i = i;
                right_i = last_pos[s[i] - 'a'];
            }
            else if (last_pos[s[i] - 'a'] > right_i)
                right_i = last_pos[s[i] - 'a'];
        }
        ans.push_back(right_i - left_i + 1);
        return ans;
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    assert(sol()->partitionLabels("ababcbacadefegdehijhklij") == vector({9, 7, 8}));
    assert(sol()->partitionLabels("eccbbbbdec") == vector({10}));
    return 0;
}
