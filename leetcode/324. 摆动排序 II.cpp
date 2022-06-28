// 324. 摆动排序 II
// https://leetcode.cn/problems/wiggle-sort-ii/
// 思维题、构造题、排序
// 数组排序后按大小切成两部分，交错构造出答案。注意一定要倒着遍历，否则无法保证“后一项小于前一项”。
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
    void wiggleSort(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        vector<int> result;
        int n = int(nums.size());
        int len2 = n / 2;
        int i = n - len2 - 1;
        int j = n - 1;
        while (i >= 0 || j >= n - len2)
        {
            if (i >= 0)
            {
                result.push_back(nums[i]);
                i--;
            }
            if (j >= n - len2)
            {
                result.push_back(nums[j]);
                j--;
            }
        }
        nums = result;
    }
};

template <class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << '[';
    bool first = true;
    for (const T &x : v)
    {
        if(first)
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
    vector<int> nums;

    nums = {1, 5, 1, 1, 6, 4};
    solution->wiggleSort(nums);
    cout << nums << endl;

    nums = {4, 5, 5, 6};
    solution->wiggleSort(nums);
    cout << nums << endl;

    nums = {1, 1, 2, 1, 2, 2, 1};
    solution->wiggleSort(nums);
    cout << nums << endl;

    delete solution;
    return 0;
}
