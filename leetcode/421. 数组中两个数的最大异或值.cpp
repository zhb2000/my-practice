#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <deque>
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

#include <ranges>

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

#include <span>
namespace rng = std::ranges;
namespace vs = std::views;

// https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array
struct Node
{
    int zero = -1;
    int one = -1;
};

class Solution
{
public:
    vector<Node> trie;

    int findMaximumXOR(vector<int> &nums)
    {
        constexpr int MAX_BIT = 31;
        // build trie
        trie.clear();
        trie.reserve(nums.size() * 31);
        trie.push_back({}); // root
        for (int num : nums)
        {
            // cout << "num: " << num << endl;
            int p = 0; // root
            for (int pos = MAX_BIT - 1; pos >= 0; pos--)
            {
                // std::cout << get_bit(num, pos) << " ";
                if (get_bit(num, pos))
                {
                    if (trie[p].one == -1)
                    {
                        trie.push_back({});
                        trie[p].one = int(trie.size()) - 1;
                    }
                    p = trie[p].one;
                }
                else
                {
                    if (trie[p].zero == -1)
                    {
                        trie.push_back({});
                        trie[p].zero = int(trie.size()) - 1;
                    }
                    p = trie[p].zero;
                }
            }
            // cout << endl;
        }

        int ans = 0;
        for (int num : nums)
        {
            int current_ans = 0;
            int p = 0; // root
            for (int pos = MAX_BIT - 1; pos >= 0; pos--)
            {
                if (get_bit(num, pos))
                {
                    if (trie[p].zero != -1)
                    {
                        current_ans = set_bit(current_ans, pos);
                        p = trie[p].zero;
                    }
                    else
                        p = trie[p].one;
                }
                else
                {
                    if (trie[p].one != -1)
                    {
                        current_ans = set_bit(current_ans, pos);
                        p = trie[p].one;
                    }
                    else
                        p = trie[p].zero;
                }
                assert(p != -1);
            }
            ans = max(ans, current_ans);
        }
        return ans;
    }

    static bool get_bit(int num, int pos)
    {
        return (num & (1 << pos)) != 0;
    }

    static int set_bit(int num, int pos)
    {
        return num | (1 << pos);
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    vector<int> nums;
    nums = {3, 10, 5, 25, 2, 8};
    assert(sol()->findMaximumXOR(nums) == 28);
    nums = {14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70};
    assert(sol()->findMaximumXOR(nums) == 127);
    return 0;
}
