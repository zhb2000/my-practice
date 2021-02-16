//P3796 【模板】AC自动机（加强版）
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

template <int maxNode, int maxN>
struct AcAuto
{
	int tr[maxNode][26];
	int fail[maxNode];
	//模式串出现的个数，-1表示已访问过
	int exist[maxNode];
	int val[maxNode];
	int node_of_id[maxN];
	int cnt;

	void reset()
	{
		cnt = 0;
		memset(tr, 0, sizeof(tr));
		memset(exist, 0, sizeof(exist));
		memset(fail, 0, sizeof(fail));
		memset(val, 0, sizeof(val));
	}

	void insert(const char *str, int id)
	{
		int p = 0;
		for (int i = 0; str[i] != '\0'; i++)
		{
			int c = str[i] - 'a';
			if (tr[p][c] == 0)
			{
				cnt++;
				tr[p][c] = cnt;
			}
			p = tr[p][c];
		}
		exist[p] += 1;
		node_of_id[id] = p;
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
	}

	void query(const char *t)
	{
		int u = 0;
		for (int i = 0; t[i] != '\0'; i++)
		{
			u = tr[u][t[i] - 'a'];
			for (int j = u; j > 0; j = fail[j])
				val[j] += 1;
		}
	}

};

const int maxnode = 155 * 75;
const int maxn = 150 + 5;
AcAuto<maxnode, maxn> ac;
string patterns[maxn];
char text[int(1e6 + 5)];

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n;
	while (scanf("%d", &n) != EOF && n > 0)
	{
		ac.reset();
		for (int i = 0; i < n; i++)
		{
			cin >> patterns[i];
			ac.insert(patterns[i].c_str(), i);
		}
		ac.build();
		scanf("%s", text);
		ac.query(text);
		int maxval = -1;
		for (int i = 0; i < n; i++)
			maxval = max(maxval, ac.val[ac.node_of_id[i]]);
		printf("%d\n", maxval);
		for (int i = 0; i < n; i++)
			if (ac.val[ac.node_of_id[i]] == maxval)
				cout << patterns[i] << "\n";
	}



#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}