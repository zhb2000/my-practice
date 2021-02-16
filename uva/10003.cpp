// 10003 Cutting Sticks 记忆化搜索

#define LOCAL

#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int INF = ~(1 << 31);
const int maxn = 50 + 5;
int a[maxn];
int d_arr[maxn][maxn];

int d(int i, int j)
{
	if (d_arr[i][j] != INF)
		return d_arr[i][j];
	if (j - i == 1)
	{
		d_arr[i][j] = 0;
		return 0;
	}
	else
	{
		for (int k = i + 1; k < j; k++)
			d_arr[i][j] = min(d_arr[i][j], d(i, k) + d(k, j) + a[j] - a[i]);
		return d_arr[i][j];
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	int l, n;
	while (scanf("%d", &l) == 1 && l != 0)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		a[0] = 0;
		a[n + 1] = l;

		for (int i = 0; i < n + 1; i++)
			for (int j = i + 1; j <= n + 1; j++)
				d_arr[i][j] = INF;

		printf("The minimum cutting is %d.\n", d(0, n + 1));
	}
	return 0;
}