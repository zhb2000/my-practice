// region header
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

#include <format>

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

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T>> &matrix)
{
    os << '[';
    bool first_row = true;
    for (const std::vector<T> &row : matrix)
    {
        if (first_row)
            first_row = false;
        else
            os << ",\n ";
        os << '[';
        bool first_col = true;
        for (const T &val : row)
        {
            if (first_col)
                first_col = false;
            else
                os << ", ";
            os << val;
        }
        os << ']';
    }
    os << ']';
    return os;
}
// endregion

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
    string decodeString(const string &s)
    {
        int n = int(s.length());
        stack<pair<int, string>> st;
        st.push({1, ""});
        for (int i = 0; i < n; i++)
        {
            if (islower(s[i]))
                st.top().second.push_back(s[i]);
            else if (isdigit(s[i]))
            {
                if (i - 1 >= 0 && isdigit(s[i - 1]))
                    st.top().first = st.top().first * 10 + (s[i] - '0');
                else
                    st.push({s[i] - '0', ""});
            }
            else if (s[i] == ']')
            {
                int cnt = st.top().first;
                string content = std::move(st.top().second);
                st.pop();
                for (int c = 1; c <= cnt; c++)
                    st.top().second.append(content);
            }
        }
        return st.top().second;
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    assert(sol()->decodeString("3[a]2[bc]") == "aaabcbc");
    assert(sol()->decodeString("abc3[cd]xyz") == "abccdcdcdxyz");
    return 0;
}
