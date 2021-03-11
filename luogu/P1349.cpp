//P1349 广义斐波那契数列
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
const double EPS = 1e-6;
//------------------------ header end ------------------------

ll mod;

struct Matrix
{
	ll data[2][2];

	Matrix operator*(const Matrix &other) const
	{
		Matrix result;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				ll sum = 0;
				for (int k = 0; k < 2; k++)
					sum = (sum + data[i][k] * other.data[k][j] % mod) % mod;
				result.data[i][j] = sum;
			}
		}
		return result;
	}
};

Matrix quick_pow(const Matrix &m, ll n)
{
	assert(n >= 1);
	if (n == 1)
		return m;
	Matrix x = quick_pow(m, n / 2);
	if (iseven(n))
		return x * x;
	else
		return x * x * m;
}

Matrix base;

ll solve(ll p, ll q, ll a1, ll a2, ll n, ll m)
{
	mod = m;
	base.data[0][0] = p;
	base.data[0][1] = 1;
	base.data[1][0] = q;
	base.data[1][1] = 0;
	if (n == 1)
		return a1;
	else if (n == 2)
		return a2;
	else
	{
		Matrix m = quick_pow(base, n - 2);
		ll result = (a2 * m.data[0][0] % mod + a1 * m.data[1][0] % mod) % mod;
		return result;
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	ll p, q, a1, a2, n, m;
	cin >> p >> q >> a1 >> a2 >> n >> m;
	cout << solve(p, q, a1, a2, n, m);


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
