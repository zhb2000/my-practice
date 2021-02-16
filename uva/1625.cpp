// 1625 Color Length

#define LOCAL

#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 2147483647;
const int maxlen = 5000 + 5;
char strn[maxlen];
char strm[maxlen];
int n, m;
int exist[maxlen][maxlen];
int d[maxlen][maxlen];
int alpha_all_time[26];
int alpha_n_time[26][maxlen];
int alpha_m_time[26][maxlen];

void calcu_alpha_time()
{
	memset(alpha_n_time, 0, sizeof(alpha_n_time));
	memset(alpha_m_time, 0, sizeof(alpha_m_time));
	for (int i = 1; i <= n; i++)
	{
		int alpha = strn[i] - 'A';
		for (int x = 0; x < 26; x++)
		{
			if (x == alpha)
				alpha_n_time[x][i] = alpha_n_time[x][i-1] + 1;
			else
				alpha_n_time[x][i] = alpha_n_time[x][i-1];
		}
	}
	for (int i = 1; i <= m; i++)
	{
		int alpha = strm[i] - 'A';
		for (int x = 0; x < 26; x++)
		{
			if (x == alpha)
				alpha_m_time[x][i] = alpha_m_time[x][i-1] + 1;
			else
				alpha_m_time[x][i] = alpha_m_time[x][i-1];
		}
	}
	for (int x = 0; x < 26; x++)
		alpha_all_time[x] = alpha_n_time[x][n] + alpha_m_time[x][m];
}
void calcu_exist()
{
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= m; j++)
		{
			exist[i][j] = 0;
			for (int x = 0; x < 26; x++)
			{
				int x_time = alpha_n_time[x][i] + alpha_m_time[x][j];
				if (x_time > 0 && x_time < alpha_all_time[x])
					exist[i][j]++;
			}
		}
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	int T;
	cin >> T;
	for (int kase = 1; kase <= T; kase++)
	{
		scanf("%s", strn + 1);
		scanf("%s", strm + 1);
		n = strlen(strn + 1);
		m = strlen(strm + 1);
		calcu_alpha_time();
		calcu_exist();

		//de
		/*for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= m; j++)
				cout << exist[i][j] << " ";
			cout << endl;
		}
		cout << endl;*/
		
		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= m; j++)
			{
				if (i == 0 && j == 0)
					d[0][0] = 0;
				else if (i == 0)
					d[0][j] = d[0][j - 1] + exist[0][j - 1];
				else if (j == 0)
					d[i][0] = d[i - 1][0] + exist[i - 1][0];
				else
					d[i][j] = min(d[i - 1][j] + exist[i - 1][j], d[i][j - 1] + exist[i][j - 1]);
			}
		}
		printf("%d\n", d[n][m]);

		//de
		/*cout << endl;
		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= m; j++)
				printf("%-2d ", d[i][j]);
			cout << endl;
		}*/
	}
	
	return 0;
}