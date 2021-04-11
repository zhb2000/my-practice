#pragma warning(disable:4996)
#pragma warning(disable:6031)
//#pragma comment(linker, "/STACK:1024000000,1024000000")
//std::ios_base::sync_with_stdio(false);
#define LOCAL
//#define DEBUG
//#define CONSOLE_PAUSE


#ifndef LOCAL
#define NDEBUG
#endif // close assert if not local
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cctype>
#include<cassert>
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
//------------------------ header end ------------------------

const int maxn = 300 + 5;
const int INF = int(1e5);
int best_ans = INF;
int n;

int colors[maxn];
vector<int> neis[maxn];

bool color_ok(int u, int color)
{
	for (int i = 0; i < int(neis[u].size()); i++)
	{
		int v = neis[u][i];
		if (colors[v] != 0 && colors[v] == color)
			return false;
	}
	return true;
}

void dfs(int u, int cur_num)
{
	if (cur_num >= best_ans)
		return;
	if (u > n)
	{
		best_ans = min(best_ans, cur_num);
		return;
	}
	for (int color = 1; color <= cur_num; color++)
	{
		if (color_ok(u, color))
		{
			colors[u] = color;
			dfs(u + 1, cur_num);
			colors[u] = 0;
		}
	}
	colors[u] = cur_num + 1;
	dfs(u + 1, cur_num + 1);
	colors[u] = 0;
}

void add_bi_edge(int u, int v)
{
	neis[u].push_back(v);
	neis[v].push_back(u);
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	n = readint();
	int m = readint();
	for (int ct = 1; ct <= m; ct++)
	{
		int u = readint();
		int v = readint();
		add_bi_edge(u, v);
	}
	dfs(1, 0);
	printf("%d", best_ans);

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}