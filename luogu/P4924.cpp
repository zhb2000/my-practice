//P4924 [1007]魔法少女小Scarlet
//模拟、递归
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
inline void cpp_io() { ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); }
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

const int maxn = 500 + 5;
int mat[maxn][maxn];
int temp[maxn];

void init_mat(int n)
{
	int num = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			mat[i][j] = num;
			num++;
		}
	}
}

void print_mat(int n)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (j != 1)
				cout << ' ';
			cout << mat[i][j];
		}
		cout << '\n';
	}
}

void mat_rotate(int x1, int y1, int x2, int y2)
{
	int len = clen(x1, x2);
	assert(len == clen(y1, y2));
	assert(len >= 1);
	assert(isodd(len));
	if (len == 1)
		return;
	for (int d = 0; d < len - 1; d++)
		temp[d] = mat[x1][y1 + d];
	for (int d = 0; d < len - 1; d++)
		mat[x1][y1 + d] = mat[x2 - d][y1];
	for (int d = 0; d < len - 1; d++)
		mat[x2 - d][y1] = mat[x2][y2 - d];
	for (int d = 0; d < len - 1; d++)
		mat[x2][y2 - d] = mat[x1 + d][y2];
	for (int d = 0; d < len - 1; d++)
		mat[x1 + d][y2] = temp[d];
	mat_rotate(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	int n, m;
	cin >> n >> m;
	init_mat(n);
	for (int c = 1; c <= m; c++)
	{
		int x, y, r, z;
		cin >> x >> y >> r >> z;
		int x1 = x - r, y1 = y - r;
		int x2 = x + r, y2 = y + r;
		int t = (z == 0) ? 1 : 3;
		for (int ct = 1; ct <= t; ct++)
			mat_rotate(x1, y1, x2, y2);
	}
	print_mat(n);


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
