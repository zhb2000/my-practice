//P1939 【模板】矩阵加速（数列）
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

const int mod = int(1e9 + 7);

struct Matrix
{
	ll data[3][3];

	Matrix operator*(const Matrix &other) const
	{
		Matrix result;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				ll sum = 0;
				for (int k = 0; k < 3; k++)
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

ll solve(ll n)
{
	if (n <= 3)
		return 1;
	else
	{
		Matrix m = quick_pow(base, n - 3);
		ll result = (m.data[0][0] + m.data[1][0] + m.data[2][0]) % mod;
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
	base.data[0][0] = 1; base.data[0][1] = 1; base.data[0][2] = 0;
	base.data[1][0] = 0; base.data[1][1] = 0; base.data[1][2] = 1;
	base.data[2][0] = 1; base.data[2][1] = 0; base.data[2][2] = 0;
	int T;
	cin >> T;
	for (int kase = 1; kase <= T; kase++)
	{
		ll n;
		cin >> n;
		cout << solve(n) << '\n';
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
