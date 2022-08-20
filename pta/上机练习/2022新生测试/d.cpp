#define LOCAL

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unordered_set>
#include <vector>
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

const int maxn = int(2e5 + 10);
int n;
ll nl[maxn];
ll nr[maxn];
vector<int> G[maxn];
int dp_f[maxn];
ll dp_v[maxn];

void dfs(int u)
{
    if (G[u].empty())
    {
        dp_f[u] = 1;
        dp_v[u] = nr[u];
        return;
    }
    int f_sum = 0;
    ll v_sum = 0;
    for (int v : G[u])
    {
        dfs(v);
        f_sum += dp_f[v];
        v_sum += dp_v[v];
    }
    if (v_sum < nl[u])
    {
        dp_f[u] = f_sum + 1;
        dp_v[u] = nr[u];
    }
    else
    {
        dp_f[u] = f_sum;
        dp_v[u] = min(v_sum, nr[u]);
    }
}

int main()
{
#ifdef LOCAL
    freopen("./in.txt", "r", stdin);
//    freopen("./out.txt", "w", stdout);
#endif
    cpp_io();

    cin >> n;
    for (int u = 2; u <= n; u++)
    {
        int parent;
        cin >> parent;
        G[parent].push_back(u);
    }
    for (int u = 1; u <= n; u++)
        cin >> nl[u] >> nr[u];
    dfs(1);
    cout << dp_f[1];

    return 0;
}
