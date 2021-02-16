// 1626 - Brackets sequence 递推法

#define LOCAL

#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int INF = ~(1 << 31);
const int maxn = 100 + 5;
char S[maxn];
char no_use[maxn];
int d[maxn][maxn];
int n;
int kase, T;

bool match(char c1, char c2)
{
	if (c1 == '('&&c2 == ')')
		return true;
	if (c1 == '['&&c2 == ']')
		return true;
	return false;
}

//void get_line_2(char *s)
//{
//	int ch;
//	int pos = 0;
//	while (true)
//	{
//		ch = getchar();
//		if (ch == EOF)
//		{
//			s[0] = '\0';
//			return;
//		}
//		if (ch != '\r'&&ch != '\n')
//			break;
//	}
//	s[pos++] = ch;
//	while (true)
//	{
//		ch = getchar();
//		if (ch == '\r' || ch == '\n' || ch == EOF)
//			break;
//		else
//			s[pos++] = ch;
//	}
//	s[pos] = '\0';
//}

void get_line(char *s)
{
	fgets(s, maxn, stdin);
	int len = strlen(s);
	for (int i = len - 1; i >= 0; i--)
	{
		if (s[i] == '\r' || s[i] == '\n')
			s[i] = '\0';
		else
			break;
	}
}

void calcu_dp()
{
	for (int i = 0; i < n; i++)
	{
		d[i + 1][i] = 0;
		d[i][i] = 1;
	}
	for (int step = 1; step < n; step++)
	{
		for (int i = 0; i + step < n; i++)
		{
			int j = i + step;
			d[i][j] = INF;
			if (match(S[i], S[j]))
				d[i][j] = min(d[i][j], d[i + 1][j - 1]);
			for (int k = i; k < j; k++)
				d[i][j] = min(d[i][j], d[i][k] + d[k + 1][j]);
		}
	}
}

void print(int i, int j)
{
	if (i > j)
		return;
	if (i == j)
	{
		if (S[i] == '(' || S[i] == ')')
			printf("()");
		else
			printf("[]");
		return;
	}
	
	int ans = d[i][j];
	if (match(S[i], S[j]) && ans == d[i + 1][j - 1])
	{
		printf("%c", S[i]);
		print(i + 1, j - 1);
		printf("%c", S[j]);
	}
	else
	{
		for (int k = i; k < j; k++)
		{
			if (ans == d[i][k] + d[k + 1][j])
			{
				print(i, k);
				print(k + 1, j);
				break;
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
	
	//cin >> T;
	fgets(no_use, maxn, stdin);
	sscanf(no_use, "%d", &T);
	for (kase = 1; kase <= T; kase++)
	{
		fgets(no_use, maxn, stdin);
		get_line(S);
		n = strlen(S);
		calcu_dp();
		print(0, n - 1);
		printf("\n");
		if (kase != T)
			printf("\n");
	}
	return 0;
}