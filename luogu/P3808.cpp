//P3808 【模板】AC自动机（简单版）
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

template <int maxNode>
struct AcAuto
{
	int tr[maxNode][26];
	int fail[maxNode];
	//模式串出现的个数，-1表示已访问过
	int exist[maxNode];
	int cnt;

	void reset()
	{
		cnt = 0;
		memset(tr, 0, sizeof(tr));
		memset(exist, 0, sizeof(exist));
		memset(fail, 0, sizeof(fail));
	}

	void insert(const char *str)
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

	//统计文本串t中模式串的出现次数
	int query(const char *t)
	{
		int u = 0, res = 0;
		for (int i = 0; t[i] != '\0'; i++)
		{
			int c = t[i] - 'a';
			u = tr[u][c];
			for (int j = u; j > 0 && exist[j] != -1; j = fail[j])
			{
				res += exist[j];
				exist[j] = -1;
			}
		}
		return res;
	}

};

const int maxnode = int(1e6 + 5);
const int maxlen = int(1e6 + 5);
AcAuto<maxnode> ac;
char s[maxlen], t[maxlen];

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	ac.reset();
	int n;
	scanf("%d", &n);
	for (int c = 1; c <= n; c++)
	{
		scanf("%s", s);
		ac.insert(s);
	}
	ac.build();
	scanf("%s", t);
	printf("%d", ac.query(t));


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}