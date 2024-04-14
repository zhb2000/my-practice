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
    vector<int> sortArray(vector<int> &nums)
    {
        quick_sort(span(nums));
        return nums;
    }

    // return (p1, p2)
    // [0, p1): x < pivot, [p1, p2): x == pivot, [p2, n): x > pivot
    template <class T>
    static pair<int, int> partition(span<T> arr, int pivot_index)
    {
        assert(!arr.empty());
        int n = int(arr.size());
        // [0 ... low-1][low ... mid-1][mid ... high][high+1 ... n-1]
        // [ x < pivot ][  x == pivot ][      ?     ][   x > pivot  ]
        int low = 0;
        int mid = 0;
        int high = n - 1;
        swap(arr[0], arr[pivot_index]);
        mid++;
        while (mid <= high)
        {
            if (arr[mid] < arr[mid - 1])
            {
                // “小于区间” [0 ... low-1] 向右增长
                // “等于区间” [low ... mid-1] 整体向右平移
                swap(arr[low], arr[mid]);
                low++;
                mid++;
            }
            else if (arr[mid] == arr[mid - 1])
                mid++; // “等于区间” [low ... mid-1] 向右增长
            else
            {
                // “大于区间” [high+1 ... n-1] 向左增长
                swap(arr[mid], arr[high]);
                high--;
            }
        }
        return {low, mid};
    }

    template <class T>
    static void quick_sort(span<T> arr)
    {
        if (arr.empty())
            return;
        auto [p1, p2] = partition(arr, (0 + arr.size()) / 2);
        quick_sort(span(arr.begin(), arr.begin() + p1)); // sort [0, p1)
        quick_sort(span(arr.begin() + p2, arr.end()));   // sort [p2, n)
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    vector<int> nums;
    nums = {5, 2, 3, 1};
    assert(sol()->sortArray(nums) == vector({1, 2, 3, 5}));
    nums = {5, 1, 1, 2, 0, 0};
    assert(sol()->sortArray(nums) == vector({0, 0, 1, 1, 2, 5}));

    nums = {-74, 48, -20, 2, 10, -84, -5, -9, 11, -24, -91, 2, -71, 64, 63, 80, 28, -30, -58, -11, -44, -87, -22, 54, -74, -10, -55, -28, -46, 29, 10, 50, -72, 34, 26, 25, 8, 51, 13, 30, 35, -8, 50, 65, -6, 16, -2, 21, -78, 35, -13, 14, 23, -3, 26, -90, 86, 25, -56, 91, -13, 92, -25, 37, 57, -20, -69, 98, 95, 45, 47, 29, 86, -28, 73, -44, -46, 65, -84, -96, -24, -12, 72, -68, 93, 57, 92, 52, -45, -2, 85, -63, 56, 55, 12, -85, 77, -39};
    vector<int> expected;
    expected = {-96, -91, -90, -87, -85, -84, -84, -78, -74, -74, -72, -71, -69, -68, -63, -58, -56, -55, -46, -46, -45, -44, -44, -39, -30, -28, -28, -25, -24, -24, -22, -20, -20, -13, -13, -12, -11, -10, -9, -8, -6, -5, -3, -2, -2, 2, 2, 8, 10, 10, 11, 12, 13, 14, 16, 21, 23, 25, 25, 26, 26, 28, 29, 29, 30, 34, 35, 35, 37, 45, 47, 48, 50, 50, 51, 52, 54, 55, 56, 57, 57, 63, 64, 65, 65, 72, 73, 77, 80, 85, 86, 86, 91, 92, 92, 93, 95, 98};
    assert(sol()->sortArray(nums) == expected);
    return 0;
}
