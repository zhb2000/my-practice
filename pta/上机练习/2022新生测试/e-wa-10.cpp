#define LOCAL

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <utility>
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

const int INF = int(1e8);
const int maxn = int(5e5 + 10);
const int maxm = maxn;
int n, m;
vector<int> G[maxn];
map<pair<int, int>, int> edge_weight;
int dp_arr[maxn];
int vis[maxn];

int dp(int u)
{
    if (u == n)
        return 0;
    if (dp_arr[u] != -1)
        return dp_arr[u];
    vis[u] = -1;
    vector<int> neighbors;
    int cut = 0;
    for (int v : G[u])
    {
        if (vis[v] == -1 || dp(v) >= INF)
            cut += edge_weight[{u, v}];
        else
            neighbors.push_back(v);
    }
    sort(neighbors.begin(), neighbors.end(),
         [](int a, int b) { return dp(a) < dp(b); });
    if (neighbors.empty())
    {
        dp_arr[u] = INF;
    }
    else
    {
        int select = neighbors[0];
        for (int i = int(neighbors.size()) - 1; i >= 1; i--)
        {
            int v = neighbors[i];
            int weight_uv = edge_weight[{u, v}];
            int vv = neighbors[i - 1];
            if (dp(vv) + weight_uv < dp(v))
            {
                cut += weight_uv;
                select = vv;
            }
            else
            {
                select = v;
                break;
            }
        }
        dp_arr[u] = 1 + dp(select) + cut;
    }
    vis[u] = 1;
    return dp_arr[u];
}

int main()
{
#ifdef LOCAL
    freopen("./in.txt", "r", stdin);
//    freopen("./out.txt", "w", stdout);
#endif
    cpp_io();

    cin >> n >> m;
    fill(dp_arr, dp_arr + n, -1);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        if (edge_weight.count({u, v}) > 0)
            edge_weight[{u, v}] += 1;
        else
        {
            G[u].push_back(v);
            edge_weight[{u, v}] = 1;
        }
    }
    int ans = dp(1);
    cout << ans;

    return 0;
}
