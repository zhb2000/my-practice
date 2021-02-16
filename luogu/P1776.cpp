//P1776 宝物筛选
//多重背包（二进制分组）
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
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<stack>
#include<queue>
#include<deque>
#include<utility>
#include<tuple>
#include<bitset>
#include<cassert>
#include<cctype>
#include<cmath>
#include<ctime>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, int> Pii;
template <class Int>
inline Int fast_read()
{
	Int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
inline int readint() { return fast_read<int>(); }
inline ll readll() { return fast_read<ll>(); }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &vec)
{
	os << "["; bool isfirst = true;
	for (const auto &x : vec)
	{
		if (isfirst) isfirst = false;
		else os << ", ";
		os << x;
	}
	os << "]"; return os;
}
template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p)
{
	os << "(" << p.first << ", " << p.second << ")"; return os;
}
template <class Int>
inline Int avg2(Int a, Int b) { if (a > b) swap(a, b); return a + ((b - a) >> 1); }
template <class Int>
inline Int clen(Int l, Int r) { if (l > r) swap(l, r); return r - l + 1; }
template <class Int>
inline bool isodd(Int num) { return (num & 1) != 0; }
template <class Int>
inline bool iseven(Int num) { return (num & 1) == 0; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-7;
//------------------------ header end ------------------------

const int maxW = int(4e4) + 5;

vector<int> w;
vector<int> v;
ll f[maxW];

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, W;
	scanf("%d%d", &n, &W);
	for (int i = 0; i < n; i++)
	{
		int value, weight, m;
		scanf("%d%d%d", &value, &weight, &m);
		int c = 1;
		while (m - c > 0)
		{
			m -= c;
			v.push_back(c * value);
			w.push_back(c * weight);
			c *= 2;
		}
		if (m > 0)
		{
			v.push_back(m * value);
			w.push_back(m * weight);
		}
	}

	n = int(v.size());
	for (int i = 0; i < n; i++)
		for (int j = W; j >= w[i]; j--)
			f[j] = max(f[j], f[j - w[i]] + v[i]);

	printf("%lld", f[W]);



#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
