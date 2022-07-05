// 1465. 切割后面积最大的蛋糕
// https://leetcode.cn/problems/maximum-area-of-a-piece-of-cake-after-horizontal-and-vertical-cuts/
// 贪心，长宽间隔都取最大即可
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <deque>
#include <iostream>
#include <map>
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

class Solution
{
public:
    int maxArea(int h, int w, vector<int> &horizontalCuts, vector<int> &verticalCuts)
    {
        using ll = long long;
        constexpr int mod = int(1e9) + 7;
        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());
        int max_h = 0;
        int last = 0;
        for (int y : horizontalCuts)
        {
            max_h = max(max_h, y - last);
            last = y;
        }
        max_h = max(max_h, h - last);
        int max_w = 0;
        last = 0;
        for (int x : verticalCuts)
        {
            max_w = max(max_w, x - last);
            last = x;
        }
        max_w = max(max_w, w - last);
        return int(ll(max_h) * max_w % mod);
    }
};

template <class T>
ostream &operator<<(ostream &os, const vector<T> &v)
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

int main()
{
    auto *solution = new Solution();

    delete solution;
    return 0;
}
