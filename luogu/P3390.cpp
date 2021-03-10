//P3390 【模板】矩阵快速幂
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

const int modu = int(1e9 + 7);

struct Matrix
{
	int n;
	vector<ll> arr;

	Matrix(int n) :n(n), arr(n * n) {}

	Matrix(const Matrix &other) = default;

	Matrix(Matrix &&other) noexcept
	{
		n = other.n;
		arr = move(other.arr);
	}

	ll &operator()(int i, int j)
	{
		return arr[i * n + j];
	}

	ll operator()(int i, int j) const
	{
		return arr[i * n + j];
	}

	Matrix operator*(const Matrix &other) const
	{
		assert(n == other.n);
		auto result = Matrix(n);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				ll sum = 0;
				for (int k = 0; k < n; k++)
					sum = (sum + (*this)(i, k) * other(k, j) % modu) % modu;
				result(i, j) = sum;
			}
		}
		return result;
	}
};

Matrix quick_pow(const Matrix &mat, ll k)
{
	assert(k >= 1);
	if (k == 1)
		return mat;
	Matrix x = quick_pow(mat, k / 2);
	if (iseven(k))
		return x * x;
	else
		return x * x * mat;
}

ostream &operator<<(ostream &os, const Matrix &mat)
{
	int n = mat.n;
	for (int i = 0; i < n; i++)
	{
		if (i > 0)
			os << '\n';
		for (int j = 0; j < n; j++)
		{
			if (j > 0)
				os << ' ';
			os << mat(i, j);
		}
	}
	return os;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	int n;
	ll k;
	cin >> n >> k;
	auto mat = Matrix(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> mat(i, j);
	Matrix result = quick_pow(mat, k);
	cout << result;


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
