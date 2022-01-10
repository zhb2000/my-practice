//括号生成
//https://leetcode-cn.com/problems/generate-parentheses
//DP
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

class Solution
{
public:
    //合法括号序列形如 (a)b
    vector<string> generateParenthesis(int n)
    {
        vector<string> f[8 + 1];
        f[0] = {""};
        f[1] = {"()"};
        for (int num = 2; num <= n; num++)
        {
            for (int head = 1; head <= num; head++)
            {
                int tail = num - head;
                for (const string &s1 : f[head - 1])
                    for (const string &s2 : f[tail])
                        f[num].push_back(string("(").append(s1).append(")").append(s2));
            }
        }
        return std::move(f[n]);
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
