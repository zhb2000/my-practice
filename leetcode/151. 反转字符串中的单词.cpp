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
    string reverseWords(string s)
    {
        const int n = int(s.size());
        string ans;
        for (int i = n - 1; i >= 0; i--)
        {
            if (s[i] == ' ' && i + 1 < n && s[i + 1] != ' ')
            {
                if (!ans.empty())
                    ans.push_back(' ');
                for (int j = i + 1; j < n && s[j] != ' '; j++)
                    ans.push_back(s[j]);
            }
        }
        if (s[0] != ' ')
        {
            if (!ans.empty())
                ans.push_back(' ');
            for (int j = 0; j < n && s[j] != ' '; j++)
                ans.push_back(s[j]);
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
