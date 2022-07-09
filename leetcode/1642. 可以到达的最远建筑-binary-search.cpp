// 1642. 可以到达的最远建筑
// https://leetcode.cn/problems/furthest-building-you-can-reach
// 二分答案
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
    int furthestBuilding(vector<int> &heights, int bricks, int ladders)
    {
        auto ladder_climb = [&](int dest) {
            vector<long long> v;
            for (int i = 1; i <= dest; i++)
                if (heights[i] > heights[i - 1])
                    v.push_back(heights[i] - heights[i - 1]);
            if (int(v.size()) <= ladders)
                return accumulate(v.begin(), v.end(), 0LL);
            nth_element(v.begin(), v.begin() + ladders, v.end(), greater<>());
            return accumulate(v.begin(), v.begin() + ladders, 0LL);
        };

        auto total_climb = [&](int dest) {
            long long total = 0;
            for (int i = 1; i <= dest; i++)
                if (heights[i] > heights[i - 1])
                    total += heights[i] - heights[i - 1];
            return total;
        };

        auto available = [&](int dest) {
            if (dest == 0)
                return true;
            return bricks + ladder_climb(dest) >= total_climb(dest);
        };

        int l = 0;
        int r = int(heights.size());
        while (l < r)
        {
            int m = l + (r - l) / 2;
            if (available(m))
                l = m + 1;
            else
                r = m;
        }
        return l - 1; // l is the upper_bound of available
    }
};

int main()
{
    auto *solution = new Solution();
    vector<int> heights;

    heights = {4, 2, 7, 6, 9, 14, 12};
    cout << solution->furthestBuilding(heights, 5, 1) << endl;

    heights = {4, 12, 2, 7, 3, 18, 20, 3, 19};
    cout << solution->furthestBuilding(heights, 10, 2) << endl;

    heights = {14, 3, 19, 3};
    cout << solution->furthestBuilding(heights, 17, 0) << endl;

    delete solution;
    return 0;
}
