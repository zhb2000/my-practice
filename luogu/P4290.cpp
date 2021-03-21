//P4290 [HAOI2008]玩具取名
//区间 DP
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
const double EPS = 1e-6;
//------------------------ header end ------------------------

char a2n[100];
const int maxn = 200 + 5;
bitset<4> f[maxn][maxn];
bitset<4> dict[4][4];
char buf[maxn];

void input_dict(char from_char, int num)
{
	int from = a2n[from_char];
	for (int i = 0; i < num; i++)
	{
		cin >> buf;
		int a1 = a2n[buf[0]];
		int a2 = a2n[buf[1]];
		dict[a1][a2][from] = true;
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	a2n['W'] = 0;
	a2n['I'] = 1;
	a2n['N'] = 2;
	a2n['G'] = 3;
	int wn, in, nn, gn;
	cin >> wn >> in >> nn >> gn;
	input_dict('W', wn);
	input_dict('I', in);
	input_dict('N', nn);
	input_dict('G', gn);
	cin >> buf;
	int n = strlen(buf);

	for (int i = 0; i < n; i++)
	{
		int a = a2n[buf[i]];
		f[i][i][a] = true;
	}

	for (int len = 2; len <= n; len++)
	{
		for (int i = 0; i < n; i++)
		{
			int j = min(i + len - 1, n - 1);
			for (int k = i; k < j; k++)
			{
				if (f[i][k].none() || f[k + 1][j].none())
					continue;
				for (int x = 0; x < 4; x++)
				{
					if (!f[i][k][x])
						continue;
					for (int y = 0; y < 4; y++)
					{
						if (!f[k + 1][j][y])
							continue;
						for (int z = 0; z < 4; z++)
						{
							if (!dict[x][y][z])
								continue;
							f[i][j][z] = true;
						}
					}
				}
			}
		}
	}

	if (f[0][n - 1].none())
		cout << "The name is wrong!";
	else
	{
		char n2a[] = "WING";
		for (int i = 0; i < 4; i++)
			if (f[0][n - 1][i])
				cout << n2a[i];
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
