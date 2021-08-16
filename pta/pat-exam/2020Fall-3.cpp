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
	int val;
	int lch = -1;
	int rch = -1;
	int floor = 0;
};

const int maxn = int(20 + 5);
int preord[maxn];
int inord[maxn];
Node ns[maxn];
int n;
int nxt_node = 1;
int new_node() { return nxt_node++; }

Pii lch_rch_size(int il, int ir, int rtv)
{
	for (int i = il; i <= ir; i++)
	{
		if (inord[i] == rtv)
		{
			return { i - il, ir - i };
		}
	}
	return { -1, -1 };
}

int build_tree(int pl, int pr, int il, int ir)
{
	//cout << "l: " << l << ", r: " << r << endl;
	assert((pr - pl) == (ir - il));
	if (pr < pl)
		return -1;
	int root = new_node();
	int rtv = preord[pl];
	int lsize, rsize;
	tie(lsize, rsize) = lch_rch_size(il, ir, rtv);
	//cout << "lsize: " << lsize << ", rsize: " << rsize <<", rtv: " << rtv << endl;
	int lch = build_tree(pl + 1, pl + lsize, il, il + lsize - 1);
	assert(pr - (pl + lsize + 1) + 1 == rsize);
	assert(ir - (il + lsize + 1) + 1 == rsize);
	int rch = build_tree(pl + lsize + 1, pr, il + lsize + 1, ir);
	ns[root].val = rtv;
	ns[root].lch = lch;
	ns[root].rch = rch;
	return root;
}

void calc_floor(int u, int floor)
{
	assert(u != -1);
	ns[u].floor = floor;
	if (ns[u].lch != -1)
		calc_floor(ns[u].lch, floor + 1);
	if (ns[u].rch != -1)
		calc_floor(ns[u].rch, floor + 1);
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	cpp_io();
	cin >> n;
	if (n == 0)
		return 0;
	for (int i = 1; i <= n; i++)
		cin >> inord[i];
	for (int i = 1; i <= n; i++)
		cin >> preord[i];
	int tree_root = build_tree(1, n, 1, n);
	calc_floor(tree_root, 1);

	vector<int> ans;
	int cur_floor = 0;
	queue<int> q;
	q.push(tree_root);
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		if (ns[u].floor != cur_floor)
		{
			assert(ns[u].floor > cur_floor);
			cur_floor = ns[u].floor;
			ans.push_back(ns[u].val);
		}
		if (ns[u].lch != -1)
			q.push(ns[u].lch);
		if (ns[u].rch != -1)
			q.push(ns[u].rch);
	}
	bool isfirst = true;
	for (int u : ans)
	{
		if (isfirst)
			isfirst = false;
		else
			cout << ' ';
		cout << u;
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
