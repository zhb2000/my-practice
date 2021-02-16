//P3366 【模板】最小生成树
//Kruskal
#include<cstdio>
#include<cstring>
#include<cctype>
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<sstream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<set>

using namespace std;

const int maxn = 5000 + 3;
const int maxm = 200000 + 3;
struct Edge
{
	int v1, v2, weight;
};
Edge edges[maxm];
int r[maxm];
int fa[maxn];
int set_size[maxn];
int n, m;
set<int> node_num;

int father(int u)
{
	if (fa[u] == u)
		return u;
	fa[u] = father(fa[u]);
	return fa[u];
}

void union_s(int x, int y)
{
	if (set_size[x] < set_size[y])
		swap(x, y);
	//y into x
	set_size[x] += set_size[y];
	fa[father(y)] = father(x);
}

void init()
{
	for (int i = 0; i < maxm; i++)
		r[i] = i;
	for (int i = 0; i < maxn; i++)
	{
		fa[i] = i;
		set_size[i] = 1;
	}
}

bool check()
{
	for (int i = 0; i < m; i++)
		union_s(edges[i].v1, edges[i].v2);
	int check_cnt = 0;
	int check_fa;
	for (int nnum : node_num)
	{
		if (check_cnt == 0)
			check_fa = father(nnum);
		else if (father(nnum) != check_fa)
			return false;
	}
	return true;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	init();
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		edges[i].v1 = x;
		edges[i].v2 = y;
		edges[i].weight = z;
		node_num.insert(x);
		node_num.insert(y);
	}
	if (!check())
	{
		printf("orz");
		return 0;
	}

	init();
	sort(r, r + m, [](int i, int j) {return edges[i].weight < edges[j].weight; });

	int weight_sum = 0;
	int edge_num = 0;
	for (int i = 0; i < m || edge_num < n - 1; i++)
	{
		int e = r[i];
		if (father(edges[e].v1) == father(edges[e].v2))
			continue;
		else
		{
			union_s(edges[e].v1, edges[e].v2);
			weight_sum += edges[e].weight;
			edge_num++;
		}
	}
	printf("%d", weight_sum);
	return 0;
}