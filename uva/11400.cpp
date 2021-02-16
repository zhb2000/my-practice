// 11400 - Lighting System Design

#define LOCAL

#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Category
{
	int V, K, C, L;
	bool operator<(const Category category)
	{
		return V < category.V;
	}
};
const int maxn = 1000 + 5;
const int INF = 2147483647;
Category cates[maxn];
int d[maxn];
int s[maxn];
int c[maxn];
int k[maxn];

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n;
	while (scanf("%d", &n) == 1 && n != 0)
	{
		for (int i = 1; i <= n; i++)
		{
			Category &lamp_cate = cates[i];
			scanf("%d%d%d%d", &lamp_cate.V, &lamp_cate.K, &lamp_cate.C, &lamp_cate.L);
		}
		
		sort(cates + 1, cates + 1 + n);
		int s_cnt = 0;
		for (int i = 1; i <= n; i++)
		{
			s_cnt += cates[i].L;
			s[i] = s_cnt;
			c[i] = cates[i].C;
			k[i] = cates[i].K;
		}
		
		s[0] = 0;
		d[0] = 0;
		for (int i = 1; i <= n; i++)
			d[i] = INF;

		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j < i; j++)
			{
				d[i] = min(d[i], d[j] + (s[i] - s[j])*c[i] + k[i]);
			}
		}
		printf("%d\n", d[n]);
	}

	return 0;
}