// P1156 垃圾陷阱
// https://www.luogu.com.cn/problem/P1156
// 背包 DP
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
// region header
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
// endregion
//------------------------ header end ------------------------

struct Garbage
{
    int time;
    int energy;
    int height;
};

const int maxn = 100 + 3;
Garbage garbages[maxn];

int main()
{
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
#endif
    cpp_io();

    int depth, n;
    cin >> depth >> n;
    for (int i = 0; i < n; i++)
        cin >> garbages[i].time >> garbages[i].energy >> garbages[i].height;
    sort(garbages, garbages + n,
         [](const Garbage &a, const Garbage &b) { return a.time < b.time; });

    // f(n, e) = h 表示只考虑前 n 个垃圾，在累计能量为 e 的条件下，所能达到的最大高度为 h
    map<int, int> f; // 滚动数组压掉 n 那一维
    f[10] = 0;       // f(-1, 10) = 0
    vector<pair<int, int>> temp;
    for (int i = 0; i < n; i++)
    {
        const Garbage &garbage = garbages[i];
        auto it = f.lower_bound(garbage.time);
        if (it == f.end())
        {
            cout << f.rbegin()->first; // max live time
            return 0;
        }
        for (; it != f.end(); ++it)
        {
            int e, h;
            tie(e, h) = *it;
            if (h + garbage.height >= depth)
            {
                cout << garbage.time;
                return 0;
            }
            temp.emplace_back(e + garbage.energy, h); // use energy
            temp.emplace_back(e, h + garbage.height); // use height
        }
        for (const auto &kv : temp) // 刷表法更新 f(n+1, e)
        {
            int e, h;
            tie(e, h) = kv;
            if (f.count(e) > 0)
                f[e] = max(f[e], h);
            else
                f[e] = h;
        }
        temp.clear();
    }
    cout << f.rbegin()->first; // max live time

    return 0;
}
