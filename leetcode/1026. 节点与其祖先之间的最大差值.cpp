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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    int maxAncestorDiff(TreeNode *root)
    {
        auto [max_diff, _min, _max] = dfs(root);
        return max_diff;
    }

    // return (max_diff, min_value, max_value)
    tuple<int, int, int> dfs(TreeNode *u)
    {
        int max_diff = 0;
        int min_value = u->val;
        int max_value = u->val;
        if (u->left != nullptr)
        {
            auto [left_max_diff, left_min_value, left_max_value] = dfs(u->left);
            max_diff = max({max_diff, left_max_diff, abs(u->val - left_min_value), abs(u->val - left_max_value)});
            min_value = min(min_value, left_min_value);
            max_value = max(max_value, left_max_value);
        }
        if (u->right != nullptr)
        {
            auto [right_max_diff, right_min_value, right_max_value] = dfs(u->right);
            max_diff = max({max_diff, right_max_diff, abs(u->val - right_min_value), abs(u->val - right_max_value)});
            min_value = min(min_value, right_min_value);
            max_value = max(max_value, right_max_value);
        }
        return {max_diff, min_value, max_value};
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
