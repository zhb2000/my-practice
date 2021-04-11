//线性分类器
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

char readchar()
{
	while (true)
	{
		char ch = char(getchar());
		if (isalpha(ch))
			return ch;
	}
}

struct Point
{
	int x, y;
	char type;
};

const int maxn = int(1e3 + 5);
Point points[maxn];
bool has[2];
int sig[2];

bool is_sig_same()
{
	return has[0] && has[1] && sig[0] * sig[1] > 0;
}

bool check(int n, int a, int b, int c)
{
	for (int i = 0; i < n; i++)
	{
		const Point &p = points[i];
		int index = p.type - 'A';
		if (!has[index])
		{
			has[index] = true;
			ll result = ll(a) * p.x + ll(b) * p.y + c;
			assert(result != 0);
			sig[index] = (result > 0) ? 1 : -1;
			if (is_sig_same())
				return false;
		}
		else
		{
			ll result = ll(a) * p.x + ll(b) * p.y + c;
			if (result * sig[index] < 0)
				return false;
		}
	}
	return true;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		points[i].x = readint();
		points[i].y = readint();
		points[i].type = readchar();
	}
#ifdef DEBUG
	for (int i = 0; i < n; i++)
		printf("p[%d]: x=%d, y=%d, type=%c\n", i, points[i].x, points[i].y, points[i].type);
#endif // DEBUG

	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &c, &a, &b);
		has[0] = has[1] = false;
		if (check(n, a, b, c))
			puts("Yes");
		else
			puts("No");
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}