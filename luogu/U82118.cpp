// U82118 【模板】Miller Rabin算法
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

// a * b % m
ll quick_mul(ll a, ll b, ll m)
{
	return ll(__int128(a) * b % m);
}

// a^n % m
ll quick_pow(ll a, ll n, ll m)
{
	ll ans = 1;
	while (n != 0)
	{
		if ((n & 1) != 0)
			ans = quick_mul(ans, a, m);
		a = quick_mul(a, a, m);
		n = n >> 1;
	}
	return ans;
}

// n is prime
bool miller_rabin(ll n)
{
	if (n <= 2)
		return n == 2;
	if (iseven(n))
		return false;
	ll u = n - 1, t = 0;
	while (iseven(u))
	{
		u = u / 2;
		t += 1;
	} // n-1 = u * 2^t
	ll A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	for (ll a : A)
	{
		ll v = quick_pow(a, u, n);
		if (v == 0)
			continue;
		if (v == 1)
			continue;
		if (v == n - 1)
			continue;
		for (int i = 1; i <= t; i++)
		{
			v = quick_mul(v, v, n);
			if (v == n - 1 && i < t)
			{
				v = 1;
				break;
			}
			else if (v == 1)
				return false;
		}
		if (v != 1)
			return false;
	}
	return true;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	cpp_io();

	ll n;
	while (cin >> n)
	{
		if (miller_rabin(n))
			cout << "Y\n";
		else
			cout << "N\n";
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
