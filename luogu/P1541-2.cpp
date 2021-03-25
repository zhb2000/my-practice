//P1541 [NOIP2010 提高组] 乌龟棋
//DP
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

const int maxn = 350 + 5;
const int maxm = 120 + 5;
const int maxnum = 40 + 2;
int f[maxnum][maxnum][maxnum][maxnum];
int goal[maxn];

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> goal[i];
	int num_a[] = { 0,0,0,0,0 };
	for (int c = 1; c <= m; c++)
	{
		int num;
		cin >> num;
		num_a[num]++;
	}
	//f[num_a[1]][num_a[2]][num_a[3]][num_a[4]] = goal[1];
	for (int a = num_a[1]; a >= 0; a--)
	{
		for (int b = num_a[2]; b >= 0; b--)
		{
			for (int c = num_a[3]; c >= 0; c--)
			{
				for (int d = num_a[4]; d >= 0; d--)
				{
					int cur = n - (a + b * 2 + c * 3 + d * 4);
					int max_last = 0;
					if (a + 1 <= num_a[1])
						max_last = max(max_last, f[a + 1][b][c][d]);
					if (b + 1 <= num_a[2])
						max_last = max(max_last, f[a][b + 1][c][d]);
					if (c + 1 <= num_a[3])
						max_last = max(max_last, f[a][b][c + 1][d]);
					if (d + 1 <= num_a[4])
						max_last = max(max_last, f[a][b][c][d + 1]);
					f[a][b][c][d] = goal[cur] + max_last;
				}
			}
		}
	}
	cout << f[0][0][0][0];


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
