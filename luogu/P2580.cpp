// P2580 于是他错误的点名开始了
//字典树
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
struct Trie
{
	int nxt[maxNode][26];
	//以该节点为结尾的单词是否出现过
	//0代表不存在，1表示存在且未访问，2代表存在且已访问
	int exist[maxNode];
	int cnt;

	void reset()
	{
		cnt = 0;
		memset(nxt, -1, sizeof(nxt));
		memset(exist, 0, sizeof(exist));
	}

	void insert(const char *str, int len)
	{
		int p = 0;
		for (int i = 0; i < len; i++)
		{
			int c = str[i] - 'a';
			if (nxt[p][c] == -1)
			{
				cnt++;
				nxt[p][c] = cnt;
			}
			p = nxt[p][c];
		}
		exist[p] = 1;
	}

	//0代表不存在，1表示存在且未访问，2代表存在且已访问
	int find(const char *str, int len)
	{
		int p = 0;
		for (int i = 0; i < len; i++)
		{
			int c = str[i] - 'a';
			if (nxt[p][c] == -1)
				return 0;
			p = nxt[p][c];
		}
		int ret = exist[p];
		if (exist[p] == 1)
			exist[p] = 2;
		return ret;
	}

};

const int maxnode = int(1e4 * 50 + 5);
Trie<maxnode> trie;

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	trie.reset();
	int n, m;
	char str[55];
	scanf("%d", &n);
	for (int c = 1; c <= n; c++)
	{
		scanf("%s", str);
		trie.insert(str, strlen(str));
	}
	scanf("%d", &m);
	for (int c = 1; c <= m; c++)
	{
		scanf("%s", str);
		switch (trie.find(str, strlen(str)))
		{
		case 0:
			puts("WRONG");
			break;
		case 1:
			puts("OK");
			break;
		case 2:
			puts("REPEAT");
			break;
		}
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}