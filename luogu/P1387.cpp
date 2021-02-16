//P1387 最大正方形
//单调栈做法
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
#include<unordered_map>
#include<stack>
#include<queue>
#include<deque>
#include<utility>
#include<tuple>
#include<bitset>
#include<cassert>
#include<cmath>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
template <class arrType>
inline arrType avg2(arrType a, arrType b) { return a + ((b - a) >> 1); }
const int nonep = -1;
const int INTMAX = ~(1 << 31);
//pick m from n, n!/(m!*(n-m)!)
ll combnum(ll n, ll m)
{
	ll sum = 1;
	for (ll i = 1; i <= m; i++)
		sum = sum * (n - m + i) / i;
	return sum;
}

const int maxlen = 2000 + 5;
int G[maxlen][maxlen];
int godown[maxlen][maxlen];
int T, n, m;
int ans;
vector<pii> st;//<j, godown_len>

void calc_godown()
{
	for (int j = 0; j < m; j++)
	{
		for (int i = n - 1; i >= 0; i--)
		{
			if (i == n - 1)
			{
				if (G[i][j] == 1)
					godown[i][j] = 1;
				else
					godown[i][j] = 0;
			}
			else
			{
				if (G[i][j] == 0)
					godown[i][j] = 0;
				else
				{
					if(G[i+1][j] == 1)
						godown[i][j] = godown[i + 1][j] + 1;
					else
						godown[i][j] = 1;
				}
			}
		}
	}
}

void calc_all(int lastj)
{
	for (const pii& p : st)
	{
		int x = p.second;
		int y = lastj - p.first + 1;
		int len = min(x, y);
		ans = max(ans, len);
	}
}

void solve()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (G[i][j] == 0)
			{
				if (!st.empty())
				{
					calc_all(j - 1);
					st.clear();
				}
			}
			else
			{
				if (st.empty())
					st.push_back(make_pair(j, godown[i][j]));
				else
				{
					if (godown[i][j] < st.back().second)
					{
						calc_all(j - 1);//calc all before modify
						int leftj = -1;//most left longer's j
						while (!st.empty()
							&& godown[i][j] <= st.back().second)//modify longer, stop when meet shorter
						{
							leftj = st.back().first;
							st.pop_back();
						}
						assert(leftj != -1);
						st.push_back(make_pair(leftj, godown[i][j]));
						int x = godown[i][j];
						int y = j - leftj + 1;
						int len = min(x, y);
						ans = max(ans, len);
					}
					else if (godown[i][j] > st.back().second)
						st.push_back(make_pair(j, godown[i][j]));
				}
				
				int leftj = j;
				while (!st.empty()
					&& godown[i][j] <= st.back().second)
				{
					leftj = st.back().first;
					st.pop_back();
				}
				st.push_back(make_pair(leftj, godown[i][j]));
				int x = godown[i][j];
				int y = j - leftj + 1;
				int len = min(x, y);
				ans = max(ans, len);
			}
		}
		//end handle
		if (!st.empty())
		{
			calc_all(m - 1);
			st.clear();
		}
	}
}

void print_godown()
{
	puts("godown:");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", godown[i][j]);
		}
		printf("\n");
	}
}

void print_graph()
{
	puts("G:");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%d", G[i][j]);
		printf("\n");
	}		
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &G[i][j]);

	//init
	ans = 0;

	calc_godown();
#ifdef DEBUG
	print_graph();
	print_godown();
#endif // DEBUG


	solve();
	printf("%d\n", ans);



#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}