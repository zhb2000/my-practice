#define LOCAL

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unordered_set>
using namespace std;
using ll = long long;

void cpp_io()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int avg2(int l, int r)
{
    return l + ((r - l) >> 1);
}

const int maxn = int(1e5 + 5);
int n;
char s[maxn];

bool check(char ch, int len)
{
    int cnt = int(count(s, s + len, ch));
    if (cnt == 0)
        return false;
    for (int i = len; i < n; i++)
    {
        if (s[i - len] == ch)
            cnt--;
        if (s[i] == ch)
            cnt++;
        if (cnt == 0)
            return false;
    }
    return true;
}

int solve_k(char ch)
{
    int l = 1;
    int r = n + 1;
    while (l < r)
    {
        int m = avg2(l, r);
        if (check(ch, m))
            r = m;
        else
            l = m + 1;
    }
    return l;
}

int main()
{
#ifdef LOCAL
    freopen("./in.txt", "r", stdin);
//    freopen("./out.txt", "w", stdout);
#endif
    cpp_io();

    cin >> s;
    n = int(strlen(s));
    int ans = n;
    for (char ch : unordered_set<char>(s, s + n))
    {
        int temp = solve_k(ch);
//        cout << "ch: " << ch << ", temp: " << temp << endl;
        ans = min(ans, temp);
    }
    cout << ans;

    return 0;
}
