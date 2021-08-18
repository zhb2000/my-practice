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
inline Int clen(Int l, Int r) { assert(l <= r); return r - l + 1; }
template <class Int>
inline bool isodd(Int num) { return (num & 1) != 0; }
template <class Int>
inline bool iseven(Int num) { return (num & 1) == 0; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-6;
//------------------------ header end ------------------------

const int maxn = 200 + 3;
int G[maxn][maxn];
int n, m;
int vis_cnt[maxn];

//1: simple cycle
//2: cycle
//3: not a cycle
int check_path(const vector<int> &path)
{
	if (path.size() == 0)
		return 3;
	if (path.front() != path.back())
		return 3;
	fill(vis_cnt + 1, vis_cnt + 1 + n, 0);
	for (int i = 0; i < int(path.size()); i++)
	{
		if (i > 0 && G[path[i - 1]][path[i]] == -1)
			return 3;
		int u = path[i];
		vis_cnt[u]++;
	}
	bool multivis = false;
	for (int i = 1; i <= n; i++)
	{
		if (i == path[0])
		{
			if (vis_cnt[i] == 0 || vis_cnt[i] == 1)
				return 3;
			else if (vis_cnt[i] > 2)
				multivis = true;
		}
		else
		{
			if (vis_cnt[i] == 0)
				return 3;
			else if (vis_cnt[i] > 1)
				multivis = true;
		}
	}
	if (multivis)
		return 2;
	else
		return 1;
}

int path_len(const vector<int> &path)
{
	int len = int(path.size());
	if (len == 0 || len == 1)
		return 0;
	int sum = 0;
	for (int i = 1; i < len; i++)
	{
		if (G[path[i - 1]][path[i]] == -1)
			return -1;
		sum += G[path[i - 1]][path[i]];
	}
	return sum;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	//cpp_io();
	scanf("%d%d", &n, &m);
	memset(G, -1, sizeof(G));
	for (int c = 1; c <= m; c++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		G[u][v] = w;
		G[v][u] = w;
	}
	int qnum;
	scanf("%d", &qnum);
	vector<int> path;
	int ans_q = -1; int ans_len = int(1e9);
	for (int q = 1; q <= qnum; q++)
	{
		path.clear();
		int plen;
		scanf("%d", &plen);
		for (int i = 0; i < plen; i++)
		{
			int u;
			scanf("%d", &u);
			path.push_back(u);
		}
		int path_type = check_path(path);
		int len = path_len(path);
		printf("Path %d: ", q);
		if (len == -1)
			printf("NA");
		else
			printf("%d", len);
		printf(" (");
		if (path_type == 1)
			printf("TS simple cycle");
		else if (path_type == 2)
			printf("TS cycle");
		else
			printf("Not a TS cycle");
		printf(")\n");
		if (path_type == 1 || path_type == 2)
		{
			assert(len != -1);
			if (len < ans_len)
			{
				ans_q = q;
				ans_len = len;
			}
		}
	}
	assert(ans_q != -1);
	printf("Shortest Dist(%d) = %d", ans_q, ans_len);



#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
