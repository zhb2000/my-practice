#pragma warning(disable:4996)
#pragma warning(disable:6031)
//#pragma comment(linker, "/STACK:1024000000,1024000000")
#define LOCAL
#define DEBUG
//#define CONSOLE_PAUSE


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
#include<numeric>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, int> Pii;
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
inline Int avg2(Int a, Int b) { assert(a <= b); return a + ((b - a) >> 1); }
template <class Int>
inline Int clen(Int l, Int r) { assert(l - 1 <= r); return r - l + 1; }
template <class Int>
inline bool isodd(Int num) { return (num & 1) != 0; }
template <class Int>
inline bool iseven(Int num) { return (num & 1) == 0; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-6;
//------------------------ header end ------------------------

const int maxs = int(1e3 + 5);
int table[maxs];
int t_size, m, n;

void insert_num(int num)
{
	int p = num % m;
	while (true)
	{
		if (table[p] != -1)
			p = (p + 1) % t_size;
		else
		{
			table[p] = num;
			break;
		}
	}
}

int fail_search(int num)
{
	int cnt = 0;
	for (int j = 0; j <= t_size; j++)
	{
		cnt++;
		int p = (num + j) % t_size;
		if (table[p] == -1)
			break;
	}
	return cnt;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	cin >> t_size >> m >> n;
	memset(table, -1, sizeof(table));
	for (int c = 1; c <= n; c++)
	{
		int num;
		cin >> num;
		insert_num(num);
	}
	int sum = 0;
	for (int num = 0; num < m; num++)
	{
		sum += fail_search(num);
		//printf("fail %d: %d\n", num, fail_search(num));
	}
	double ans = double(sum) / m;
	printf("%.1lf", ans);


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
