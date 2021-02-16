// P5357 【模板】AC自动机（二次加强版）
// 拓扑排序优化
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
const double EPS = 1e-7;
//------------------------ header end ------------------------

template<int maxNode>
struct AcAuto
{
	int tr[maxNode][26];
	int fail[maxNode];
	int ans[maxNode];
	bool is_pattern[maxNode];
	int topo_vis[maxNode];
	vector<int> topo;
	int cnt = 0;

	void clear()
	{
		cnt = 0;
		memset(tr, 0, sizeof(tr));
		memset(fail, 0, sizeof(fail));
		memset(ans, 0, sizeof(ans));
		memset(is_pattern, 0, sizeof(is_pattern));
		memset(topo_vis, 0, sizeof(topo_vis));
		topo.clear();
	}

	//return: node in tree
	int insert(const char *pattern)
	{
		int p = 0;
		for (int i = 0; pattern[i] != '\0'; i++)
		{
			int c = pattern[i] - 'a';
			if (tr[p][c] == 0)
			{
				cnt++;
				tr[p][c] = cnt;
			}
			p = tr[p][c];
		}
		is_pattern[p] = true;
		return p;
	}

	void topo_dfs(int u)
	{
		topo_vis[u] = -1;
		int v = fail[u];
		if (v != 0)
		{
			assert(topo_vis[v] != -1);
			if (topo_vis[v] == 0)
				topo_dfs(v);
		}
		topo_vis[u] = 1;
		topo.push_back(u);
	}

	void topo_sort()
	{
		for (int u = 1; u <= cnt; u++)
			if (topo_vis[u] == 0)
				topo_dfs(u);
		reverse(topo.begin(), topo.end());
	}

	void build()
	{
		queue<int> q;
		for (int i = 0; i < 26; i++)
			if (tr[0][i] != 0)
				q.push(tr[0][i]);
		while (!q.empty())
		{
			int u = q.front(); q.pop();
			for (int i = 0; i < 26; i++)
			{
				if (tr[u][i] != 0)
				{
					fail[tr[u][i]] = tr[fail[u]][i];
					q.push(tr[u][i]);
				}
				else
					tr[u][i] = tr[fail[u]][i];
			}
		}
		topo_sort();
	}

	void query(const char *text)
	{
		int u = 0;
		for (int i = 0; text[i] != '\0'; i++)
		{
			int c = text[i] - 'a';
			u = tr[u][c];
			ans[u]++;
		}
		for (int u : topo)
		{
			int v = fail[u];
			if (v != 0)
				ans[v] += ans[u];
		}
	}
};

const int maxn = int(2e5 + 10);
AcAuto<maxn> ac;
unordered_set<string> pattern_set;
unordered_map<string, int> node_in_tree;
vector<string> pattern_vec;

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	string line;
	for (int ct = 1; ct <= n; ct++)
	{
		cin >> line;
		pattern_vec.push_back(line);
		if (pattern_set.count(line) == 0)
		{
			pattern_set.insert(line);
			node_in_tree[line] = ac.insert(line.c_str());
		}
	}
	ac.build();
	cin >> line;
	ac.query(line.c_str());
	for (const string &ps : pattern_vec)
	{
		cout << ac.ans[node_in_tree[ps]] << "\n";
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}