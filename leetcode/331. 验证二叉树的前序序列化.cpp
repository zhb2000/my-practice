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

class Solution
{
public:
    bool isValidSerialization(const string &preorder)
    {
        vector<int> sequence = split(preorder);
        const int n = int(sequence.size());
        int index = 0;
        std::function<bool()> tree_ok = [&] {
            index++;
            const int i = index - 1;
            if (i >= n)
                return false;
            if (sequence[i] == -1)
                return true;
            if (!tree_ok()) // left sub-tree
                return false;
            if (!tree_ok()) // right sub-tree
                return false;
            return true;
        };
        if (!tree_ok())
            return false;
        if (index != n)
        {
            assert(index < n);
            return false;
        }
        return true;
    }

    static vector<int> split(string_view s)
    {
        vector<int> seq;
        string temp;
        for (char ch : s)
        {
            if (ch == ',')
            {
                if (temp == "#")
                    seq.push_back(-1);
                else
                    seq.push_back(std::stoi(temp));
                temp.clear();
            }
            else
                temp.push_back(ch);
        }
        assert(!temp.empty());
        if (temp == "#")
            seq.push_back(-1);
        else
            seq.push_back(std::stoi(temp));
        return seq;
    }
};

std::unique_ptr<Solution> sol()
{
    return std::make_unique<Solution>();
}

int main()
{
    assert(sol()->isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#"));
    assert(!sol()->isValidSerialization("1,#"));
    assert(!sol()->isValidSerialization("9,#,#,1"));
    cout << sol()->isValidSerialization("#") << endl;
    cout << sol()->isValidSerialization("100") << endl;
    return 0;
}
