// P1341 无序字母对
// https://www.luogu.com.cn/problem/P1341
// 无向图字典序最小的欧拉路径

#ifndef LOCAL
#define NDEBUG
#endif // close assert if not local
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
//#region header
// clang-format off
using namespace std;
typedef long long ll; typedef unsigned long long ull; typedef unsigned int uint;
typedef pair<int, int> Pii;
template<class T, class Hasher = hash<T>, class Eq = equal_to<T>, class A = allocator<T>>
using uset = unordered_set<T, Hasher, Eq, A>;
template<class K, class V, class Hasher = hash<K>, class Eq = equal_to<K>, class A = allocator<K>>
using umap = unordered_map<K, V, Hasher, Eq, A>;
template <class Int>
inline Int fast_read()
{
    Int x = 0, f = 1; char ch = char(getchar());
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = char(getchar()); }
    while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = char(getchar()); }
    return x * f;
}
inline int readint() { return fast_read<int>(); }
inline ll readll() { return fast_read<ll>(); }
inline void cpp_io() { ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); }
template<class Container>
ostream &output_sequence(ostream &os, const Container &container, const char *l, const char *r);
template<class T, class A>
ostream &operator<<(ostream &os, const vector<T, A> &v) { return output_sequence(os, v, "[", "]"); }
template<class T, class Cmp, class A>
ostream &operator<<(ostream &os, const set<T, Cmp, A> &s) { return output_sequence(os, s, "{", "}"); }
template<class T, class Hasher, class Eq, class A>
ostream &operator<<(ostream &os, const uset<T, Hasher, Eq, A> &s) { return output_sequence(os, s, "{", "}"); }
template<class Container>
ostream &output_sequence(ostream &os, const Container &container, const char *l, const char *r)
{
    os << l; bool isfirst = true;
    for (const auto &x : container) { if (isfirst) isfirst = false; else os << ", "; os << x; }
    os << r; return os;
}
template<class Map>
ostream &output_map(ostream &os, const Map &m);
template<class K, class V, class Cmp, class A>
ostream &operator<<(ostream &os, const map<K, V, Cmp, A> &m) { return output_map(os, m); }
template<class K, class V, class Hasher, class Eq, class A>
ostream &operator<<(ostream &os, const umap<K, V, Hasher, Eq, A> &m) { return output_map(os, m); }
template<class Map>
ostream &output_map(ostream &os, const Map &m)
{
    os << "{"; bool isfirst = true;
    for (const auto &kv : m) { if (isfirst) isfirst = false; else os << ", "; os << kv.first << ": " << kv.second; }
    os << "}"; return os;
}
template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) { return os << "(" << p.first << ", " << p.second << ")"; }
template <class Int>
inline Int avg2(Int a, Int b) { assert(a <= b); return a + ((b - a) >> 1); }
template <class Int>
inline Int clen(Int l, Int r) { assert(l - 1 <= r); return r - l + 1; }
template <class Int>
inline bool isodd(Int num) { return (num & 1) != 0; }
template <class Int>
inline bool iseven(Int num) { return (num & 1) == 0; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-8;
inline int sgn(double x) { if (x < -EPS) return -1; if (x > EPS) return 1; return 0; }
// clang-format on
//#endregion
//------------------------ header end ------------------------

char i2a(int i) { return i < 26 ? 'A' + i : 'a' + (i - 26); }
int a2i(char a) { return isupper(a) ? a - 'A' : a - 'a' + 26; }

const int maxv = 26 * 2 + 3;

bool G[maxv][maxv]; // 邻接矩阵存图
unordered_set<int> node_set;
bool node_vis[maxv];
int degree[maxv];
int cur[maxv];
vector<int> st;

// 判断连通性
void node_dfs(int u)
{
    node_vis[u] = true;
    for (int v = 0; v < 26 * 2; v++)
        if (G[u][v] && !node_vis[v])
            node_dfs(v);
}

int start_node()
{
    node_dfs(*node_set.begin());
    for (int u : node_set)
        if (!node_vis[u])
            return -1;
    const int INF = int(1e5);
    int min_node = INF;
    int min_odd_node = INF;
    int odd_node_num = 0;
    for (int u : node_set)
    {
        min_node = min(min_node, u);
        if (isodd(degree[u]))
        {
            odd_node_num++;
            min_odd_node = min(min_odd_node, u);
        }
    }
    if (odd_node_num == 0)
        return min_node;
    else if (odd_node_num == 2)
        return min_odd_node;
    else
        return -1;
}

void dfs(int u)
{
    for (int v = cur[u]; v < 26 * 2; v = cur[u])
    {
        cur[u]++;
        if (G[u][v])
        {
            G[u][v] = G[v][u] = false; // 删边
            dfs(v);
        }
    }
    st.push_back(u);
}

int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
#endif
    cpp_io();
    int m;
    cin >> m;
    for (int e = 0; e < m; e++)
    {
        char edge[3];
        cin >> edge;
        int u = a2i(edge[0]), v = a2i(edge[1]);
        G[u][v] = G[v][u] = true;
        degree[u]++;
        degree[v]++;
        node_set.insert(u);
        node_set.insert(v);
    }
    int start = start_node();
    if (start == -1)
        cout << "No Solution";
    else
    {
        dfs(start);
        reverse(st.begin(), st.end());
        for (int u : st)
            cout << i2a(u);
    }
    return 0;
}
