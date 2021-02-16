//P1523 旅行商简化版
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

using namespace std;

const double INF = 1e11;
const int maxn = 1000 + 5;
struct Point
{
	double x, y;
	bool operator<(const Point &p) const
	{
		return x < p.x;
	}
};

Point points[maxn];
double f[maxn][maxn];

double dist(int i, int j)
{
	double x_i = points[i].x;
	double y_i = points[i].y;
	double x_j = points[j].x;
	double y_j = points[j].y;
	return sqrt((x_i - x_j)*(x_i - x_j) + (y_i - y_j)*(y_i - y_j));
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		scanf("%lf%lf", &points[i].x, &points[i].y);
	sort(points, points + n);
	for (int j = 0; j < n; j++)
		for (int i = 0; i <= j; i++)
			f[i][j] = INF;

	f[0][1] = dist(0, 1);
	for (int j = 1; j + 1 < n; j++)
	{
		for (int i = 0; i < j; i++)
			f[i][j + 1] = min(f[i][j + 1], f[i][j] + dist(j, j + 1));
		for (int i = 0; i < j; i++)
			f[j][j + 1] = min(f[j][j + 1], f[i][j] + dist(i, j + 1));
	}
	/*for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			f[i][j + 1] = min(f[i][j + 1], f[i][j] + dist(j, j + 1));
			f[j][j + 1] = min(f[j][j + 1], f[i][j] + dist(i, j + 1));
		}
	}*/
	double ans = INF;
	for (int i = 0; i <= n - 2; i++)
		ans = min(ans, f[i][n - 1] + dist(i, n - 1));
	printf("%.2lf", ans);
	return 0;
}