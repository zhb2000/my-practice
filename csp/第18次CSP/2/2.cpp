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

set<Pii> points;

int nei_deltx[] = { 0,1,0,-1 };
int nei_delty[] = { 1,0,-1,0 };
bool is_station(const Pii &p)
{
	int x = p.first, y = p.second;
	for (int i = 0; i < 4; i++)
		if (points.count(
			make_pair(x + nei_deltx[i], y + nei_delty[i])) == 0)
			return false;
	return true;
}

int cor_deltx[] = { -1,1,1,-1 };
int cor_delty[] = { 1,1,-1,-1 };
int station_score(const Pii &p)
{
	int x = p.first, y = p.second;
	int score = 0;
	for (int i = 0; i < 4; i++)
		if (points.count(
			make_pair(x + cor_deltx[i], y + cor_delty[i])))
			score++;
	return score;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		points.insert(make_pair(x, y));
	}
	int cnt[] = { 0,0,0,0,0 };
	for (const auto &p : points)
	{
		if (is_station(p))
			cnt[station_score(p)]++;
	}
	for (int score = 0; score <= 4; score++)
	{
		printf("%d", cnt[score]);
		if (score != 4)
			printf("\n");
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}