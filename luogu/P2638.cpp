//组合数学、隔板法
#ifndef LOCAL
#define NDEBUG
#endif // close assert if not local
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<functional>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<queue>
#include<deque>
#include<bitset>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<tuple>
#include<cassert>
#include<cctype>
#include<cmath>
#include<numeric>
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
	for (const auto &kv : m)
	{
		if (isfirst) isfirst = false; else os << ", ";
		os << kv.first << ": " << kv.second;
	}
	os << "}"; return os;
}
template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p)
{
	os << "(" << p.first << ", " << p.second << ")"; return os;
}
template <class Int>
inline Int avg2(Int a, Int b) { assert(a <= b); return a + ((b - a) >> 1); }
template <class Int>
inline Int clen(Int l, Int r) { assert(l - 1 <= r); return r - l + 1; }
template <class Int>
inline bool isodd(Int num) { return (num & 1) != 0; }
template <class Int>
inline bool iseven(Int num) { return (num & 1) == 0; }
#define foreach(x, seq) for (const auto &x : seq)
const int INTMAX = ~(1 << 31);
const double EPS = 1e-8;
inline int sgn(double x) { if (x < -EPS) return -1; if (x > EPS) return 1; return 0; }
//------------------------ header end ------------------------

const int maxn = 50 + 5;
ull comb[maxn][maxn];

void calc_comb(int top)
{
	for (int x = 0; x <= top; x++)
		comb[x][0] = 1;
	for (int x = 1; x <= top; x++)
		for (int y = 1; y <= x; y++)
			comb[x][y] = comb[x - 1][y - 1] + comb[x - 1][y];
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	int n, a, b;
	cin >> n >> a >> b;
	calc_comb(50);
	ull ans = 0;
	for (int i = 0; i <= a; i++)
		for (int j = 0; j <= b; j++)
			ans += comb[i + n - 1][n - 1] * comb[j + n - 1][n - 1];
	cout << ans;

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
