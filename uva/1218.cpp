// 1218 - Perfect Service

#define LOCAL

#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

//const int INF = ~(1 << 31);
const int INF = 10002;
const int maxn = 10000 + 5;
vector<int> childs[maxn];
int d_arr[maxn][3];

int d(int u, int status)
{
	if (d_arr[u][status] != -1)
		return d_arr[u][status];

	if (status == 0)
	{
		d_arr[u][0] = 1;
		for (int v : childs[u])
			d_arr[u][0] += min(d(v, 0), d(v, 1));
		return d_arr[u][0];
	}
	else if (status == 1)
	{
		d_arr[u][1] = 0;
		for (int v : childs[u])
			d_arr[u][1] += d(v, 2);
		return d_arr[u][1];
	}
	else
	{
		d_arr[u][2] = INF;
		for (int v : childs[u])
			d_arr[u][2] = min(d_arr[u][2], d(u, 1) - d(v, 2) + d(v, 0));
		return d_arr[u][2];
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	while (true)
	{
		int n;
		scanf("%d", &n);

		for (int u = 1; u <= n; u++)
			childs[u].clear();
		for (int u = 1; u <= n; u++)
			for (int status = 0; status <= 2; status++)
				d_arr[u][status] = -1;

		int father, child;
		for (int cnt = 1; cnt <= n - 1; cnt++)
		{
			scanf("%d%d", &father, &child);
			if (father > child)
				swap(father, child);
			childs[father].push_back(child);
		}
		printf("%d\n", min(d(1, 0), d(1, 2)));
		int flag;
		scanf("%d", &flag);
		if (flag == -1)
			break;
	}
	return 0;
}