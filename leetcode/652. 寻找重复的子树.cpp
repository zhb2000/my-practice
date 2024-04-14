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

template <>
struct std::hash<tuple<int, size_t, size_t>>
{
    size_t operator()(const tuple<int, size_t, size_t> &triplet) const
    {
        auto [value, left, right] = triplet;
        value += 200;
        return size_t(value) * 5001 * 5001 + left * 5001 + right;
    }
};

class Solution
{
public:
    vector<TreeNode *> findDuplicateSubtrees(TreeNode *root)
    {
        vector<TreeNode *> ans;
        unordered_set<size_t> ans_ids;
        unordered_map<tuple<int, size_t, size_t>, size_t> subtrees;
        function<size_t(TreeNode *)> traverse = [&](TreeNode *u) {
            if (u == nullptr)
                return size_t(5001);
            size_t left_id = traverse(u->left);
            size_t right_id = traverse(u->right);
            auto triplet = make_tuple(u->val, left_id, right_id);
            if (subtrees.contains(triplet))
            {
                size_t id = subtrees[triplet];
                if (!ans_ids.contains(id))
                {
                    ans.push_back(u);
                    ans_ids.insert(id);
                }
                return id;
            }
            size_t id = subtrees.size();
            subtrees[triplet] = id;
            return id;
        };
        traverse(root);
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
