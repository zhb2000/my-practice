// 247 Calling Circles
//#pragma warning(disable: 6031)
//#include "pch.h"

#define LOCAL
//#define DEBUG

#include<cstdio>
#include<cstring>
#include<cctype>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<unordered_map>
#include<sstream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<set>
#include<tuple>
#include<utility>

using namespace std;
typedef long long LL;

const int maxn = 25 + 2;
int fa[maxn];
int setsize[maxn];
int n, m, kase;
bool d[maxn][maxn];
unordered_map<string, int> dict;
string names[maxn];
vector<string*> circles[maxn];

int father(int u)
{
	if (fa[u] == u)
		return u;
	fa[u] = father(fa[u]);
	return fa[u];
}

void unionset(int x, int y)
{
	if (father(x) == father(y))
		return;

	if (setsize[x] < setsize[y])
		swap(x, y);
	//y into x
	fa[father(y)] = father(x);
	setsize[father(x)] += setsize[father(y)];
}

void init_set()
{
	for (int i = 0; i < n; i++)
	{
		fa[i] = i;
		setsize[i] = 1;
	}
}

//d, dict, circles
void init()
{
	for(int i=0;i<n;i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				d[i][j] = true;
			else
				d[i][j] = false;
		}
	dict.clear();
	for (int i = 0; i < n; i++)
		circles[i].clear();
}

void floyd()
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				d[i][j] = d[i][j] || (d[i][k] && d[k][j]);
}

//getnum or insert
inline int getnum(const string& name)
{
	int num = (int)dict.size();
	if (dict.count(name) != 0)
		return dict[name];
	dict[name] = num;
	names[num] = name;
	return num;
}

void build_circle()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (d[i][j] && d[j][i])
				unionset(i, j);
		}
	}
	for (int u = 0; u < n; u++)
		circles[father(u)].push_back(&names[u]);
}

void output()
{
	if (kase != 1)
		printf("\n");
	printf("Calling circles for data set %d:\n", kase);
	for (int i = 0; i < n; i++)
	{
		if (!circles[i].empty())
		{
			bool is_first = true;
			for (string* name : circles[i])
			{
				if (!is_first)
					printf(", ");
				else
					is_first = false;
				cout << *name;
			}
			printf("\n");
		}
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	kase = 1;
	while (scanf("%d%d", &n, &m) == 2 && !(n == 0 && m == 0))
	{
		init();
		init_set();
		for (int c = 1; c <= m; c++)
		{
			string from, to;
			cin >> from >> to;
			int i = getnum(from);
			int j = getnum(to);
			d[i][j] = true;
		}
		floyd();
		build_circle();
		output();
		kase++;
	}
	
	return 0;
}