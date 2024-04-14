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

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x)
        : val(x), left(NULL), right(NULL) {}
};

class Codec
{
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        string result;
        do_serialize(root, result);
        return result;
    }

    void do_serialize(TreeNode *root, string &result)
    {
        if (root == nullptr)
        {
            result.append("#,");
            return;
        }
        result.append(std::to_string(root->val)).append(",");
        do_serialize(root->left, result);
        do_serialize(root->right, result);
    }

    static constexpr int NONE = -2000;

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        vector<int> seq = split(data);
        span<int> rest_seq = seq;
        return do_deserialized(rest_seq);
    }

    vector<int> split(string_view s)
    {
        vector<int> seq;
        string temp;
        for (char ch : s)
        {
            if (ch == ',')
            {
                if (temp == "#")
                    seq.push_back(NONE);
                else
                    seq.push_back(stoi(temp));
                temp.clear();
            }
            else
                temp.push_back(ch);
        }
        assert(temp.empty());
        return seq;
    }

    TreeNode *do_deserialized(span<int> &rest_seq)
    {
        assert(!rest_seq.empty());
        if (rest_seq[0] == NONE)
        {
            rest_seq = rest_seq.subspan(1);
            return nullptr;
        }
        auto node = new TreeNode(rest_seq[0]);
        rest_seq = rest_seq.subspan(1);
        node->left = do_deserialized(rest_seq);
        node->right = do_deserialized(rest_seq);
        return node;
    }
};

class Solution
{};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    return 0;
}
