//括号生成
//https://leetcode-cn.com/problems/generate-parentheses
//DFS + 剪枝
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

template <class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "[";
    bool isfirst = true;
    for (const auto &x : v)
    {
        if (isfirst)
            isfirst = false;
        else
            os << ", ";
        os << x;
    }
    os << "]";
    return os;
}

// DFS 尝试添加左右括号
// 剪枝：只有左括号个数大于等于右括号个数时继续加括号才有意义
class Solution
{
public:
    vector<string> generateParenthesis(int n)
    {
        int len = n * 2;
        vector<string> result;
        string temp;
        dfs(0, len, 0, 0, temp, result);
        return result;
    }

    void dfs(int cur, int len, int lnum, int rnum, string &temp, vector<string> &result)
    {
        if (cur == len)
        {
            if (lnum == rnum)
                result.push_back(temp);
            return;
        }
        assert(lnum >= rnum);
        assert(cur == int(temp.length()));
        auto push_left = [&] {
            temp.push_back('(');
            dfs(cur + 1, len, lnum + 1, rnum, temp, result);
            assert(!temp.empty() && temp.back() == '(');
            temp.pop_back();
        };
        auto push_right = [&] {
            temp.push_back(')');
            dfs(cur + 1, len, lnum, rnum + 1, temp, result);
            assert(!temp.empty() && temp.back() == ')');
            temp.pop_back();
        };
        if (lnum > rnum)
        {
            push_left();
            push_right();
        }
        else // lnum == rnum
        {
            assert(lnum == rnum);
            push_left();
        }
    }
};

int main()
{
    auto sol = new Solution();

    cout << sol->generateParenthesis(3) << endl;
    cout << sol->generateParenthesis(1) << endl;
    cout << sol->generateParenthesis(8) << endl;

    delete sol;
    return 0;
}
