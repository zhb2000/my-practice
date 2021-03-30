//P1004 [NOIP2000 提高组] 方格取数
//DFS、记忆化搜索
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

const int maxn = 9 + 3;
int mat[maxn][maxn];
int f_arr[maxn][maxn][maxn][maxn];
int n;

int f(int a, int b, int c, int d)
{
	if (f_arr[a][b][c][d] != -1)
		return f_arr[a][b][c][d];
	int ab = mat[a][b];
	mat[a][b] = 0;
	int cd = mat[c][d];
	mat[c][d] = 0;
	int max_next = 0;
	if (a + 1 <= n && c + 1 <= n)
		max_next = max(max_next, f(a + 1, b, c + 1, d));
	if (a + 1 <= n && d + 1 <= n)
		max_next = max(max_next, f(a + 1, b, c, d + 1));
	if (b + 1 <= n && c + 1 <= n)
		max_next = max(max_next, f(a, b + 1, c + 1, d));
	if (b + 1 <= n && d + 1 <= n)
		max_next = max(max_next, f(a, b + 1, c, d + 1));
	mat[c][d] = cd;
	mat[a][b] = ab;
	f_arr[a][b][c][d] = ab + cd + max_next;
	return f_arr[a][b][c][d];
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	cin >> n;
	memset(f_arr, -1, sizeof(f_arr));
	while (true)
	{
		int i, j, num;
		cin >> i >> j >> num;
		if (i == 0 && j == 0 && num == 0)
			break;
		mat[i][j] = num;
	}
	cout << f(1, 1, 1, 1);

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
