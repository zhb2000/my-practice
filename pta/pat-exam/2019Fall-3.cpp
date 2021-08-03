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
inline Int avg2(Int a, Int b) { assert(a <= b); return a + ((b - a) >> 1); }
template <class Int>
inline Int clen(Int l, Int r) { assert(l <= r); return r - l + 1; }
template <class Int>
inline bool isodd(Int num) { return (num & 1) != 0; }
template <class Int>
inline bool iseven(Int num) { return (num & 1) == 0; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-6;
//------------------------ header end ------------------------

struct Node
{
	char data[15];
	int lch;
	int rch;
	int fa = -1;
};

const int maxn = 100;
Node ns[maxn];

int find_root(int n)
{
	for (int i = 1; i <= n; i++)
		if (ns[i].fa == -1)
			return i;
	return -1;
}

void postorder(int u)
{
	if (u == -1)
		return;

	if (ns[u].lch != -1 && ns[u].rch == -1)
	{
		cout << '(';
		cout << ns[u].data;
		postorder(ns[u].lch);
		cout << ')';
		return;
	}
	if (ns[u].lch == -1 && ns[u].rch != -1)
	{
		cout << '(';
		cout << ns[u].data;
		postorder(ns[u].rch);
		cout << ')';
		return;
	}

	cout << '(';
	postorder(ns[u].lch);
	postorder(ns[u].rch);
	cout << ns[u].data;
	cout << ')';
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	int n;
	cin >> n;
	if (n == 0)
	{
		printf("\n");
		return 0;
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> ns[i].data >> ns[i].lch >> ns[i].rch;
		if (ns[i].lch != -1)
			ns[ns[i].lch].fa = i;
		if (ns[i].rch != -1)
			ns[ns[i].rch].fa = i;
	}
	int root = find_root(n);
	assert(root != -1);
	postorder(root);



#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
