// 968. 监控二叉树
// https://leetcode.cn/problems/binary-tree-cameras/
// 树形 DP
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

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode()
        : val(0),
          left(nullptr),
          right(nullptr) {}
    TreeNode(int x)
        : val(x),
          left(nullptr),
          right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x),
          left(left),
          right(right) {}
};

class Solution
{
public:
    // - a: self installed
    // - b: self not installed, covered by parent
    // - c: self not installed, covered by children
    static tuple<int, int, int> dfs(TreeNode *root)
    {
        const int INF = int(1e8);
        if (root == nullptr)
            return {INF, 0, 0};
        auto [la, lb, lc] = dfs(root->left);
        auto [ra, rb, rc] = dfs(root->right);
        int a = 1 + min({la, lb, lc}) + min({ra, rb, rc});
        int b = min(la, lc) + min(ra, rc);
        int c = min({la + ra, la + rc, lc + ra});
        return {a, b, c};
    }

    static int minCameraCover(TreeNode *root)
    {
        auto [a, b, c] = dfs(root);
        return min({a, c});
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
    return 0;
}
