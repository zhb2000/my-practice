// 1220 - Party at Hali-Bula

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

const int INF = ~(1 << 31);
const int maxn = 200 + 5;
map<string, int> code_map;
vector<int> childs[maxn];
int f[maxn][2];
int d_arr[maxn][2];
int best_ans;
int is_unique;
int n;

int d(int u, int status)
{
	if (d_arr[u][status] != -1)
		return d_arr[u][status];

	if (status == 1)
	{
		d_arr[u][1] = 1;
		f[u][1] = 1;
		for (int v : childs[u])
		{
			d_arr[u][1] += d(v, 0);
			if (f[v][0] == 0)
				f[u][1] = 0;
		}
		return d_arr[u][1];
	}
	else
	{
		d_arr[u][0] = 0;
		f[u][0] = 1;
		for (int v : childs[u])
		{
			if (d(v, 0) == d(v, 1))
			{
				d_arr[u][0] += d(v, 0);
				f[u][0] = 0;
			}
			else if (d(v, 0) > d(v, 1))
			{
				d_arr[u][0] += d(v, 0);
				if (f[v][0] == 0)
					f[u][0] = 0;
			}
			else
			{
				d_arr[u][0] += d(v, 1);
				if (f[v][1] == 0)
					f[u][0] = 0;
			}
		}
		return d_arr[u][0];
	}
}

void calcu_dp()
{
	for (int u = 1; u <= n; u++)
	{
		for (int status = 0; status <= 1; status++)
		{
			int d_u_s = d(u, status);
			if (d_u_s > best_ans)
			{
				best_ans = d_u_s;
				is_unique = f[u][status];
			}
			else if (d_u_s == best_ans)
				is_unique = 0;
		}
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	while (scanf("%d", &n) == 1 && n != 0)
	{
		best_ans = -1;
		code_map.clear();
		for (int u = 1; u <= n; u++)
			childs[u].clear();
		for (int u = 1; u <= n; u++)
			for (int status = 0; status <= 1; status++)
				d_arr[u][status] = -1;

		string big_boss, employee, boss;
		cin >> big_boss;
		code_map[big_boss] = 1;
		for (int i = 2; i <= n; i++)
		{
			cin >> employee >> boss;
			int employee_code;
			if (code_map.count(employee))
				employee_code = code_map[employee];
			else
			{
				employee_code = code_map.size() + 1;
				code_map[employee] = employee_code;
			}
			code_map[employee] = employee_code;
			int boss_code;
			if (code_map.count(boss))
				boss_code = code_map[boss];
			else
			{
				boss_code = code_map.size() + 1;
				code_map[boss] = boss_code;
			}
			childs[boss_code].push_back(employee_code);
		}
		calcu_dp();
		printf("%d ", best_ans);
		if (is_unique == 1)
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}