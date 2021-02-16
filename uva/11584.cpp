// 11584 Partitioning by Palindromes

#define LOCAL

#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 2147483647;
const int maxlen = 1000 + 5;
char input_str[maxlen];
char split_str[maxlen * 2];
int palin_arr[maxlen][maxlen];
int d[maxlen];

int is_palin(int x, int y)
{
	if (palin_arr[x][y] != -1)
		return palin_arr[x][y];
	if (x == y)
	{
		palin_arr[x][x] = 1;
		return 1;
	}
	if (y - x == 1)
	{
		palin_arr[x][y] = (input_str[x] == input_str[y] ? 1 : 0);
		return palin_arr[x][y];
	}
	if (input_str[x] != input_str[y])
	{
		palin_arr[x][y] = 0;
		return 0;
	}
	else
	{
		return is_palin(x + 1, y - 1);
	}
}

//bool is_palin(int x, int y)
//{
//	if (x > y)
//		return false;
//	if (x == y)
//		return true;
//	else
//		return palin_arr[x][y];
//}

void pre_calcu(char *origin_str, int origin_len)
{
	memset(palin_arr, 0, sizeof(palin_arr));
	for (int i = 1; i <= origin_len * 2 + 1; i++)
	{
		if (i % 2 != 0)
			split_str[i] = '#';
		else
			split_str[i] = origin_str[i >> 1];
	}
	for (int pivot = 2; pivot <= origin_len * 2; pivot++)
	{
		for (int step = 1;; step++)
		{
			int left_bnd = pivot - step;
			int right_bnd = pivot + step;
			if (left_bnd<1 || right_bnd>origin_len * 2 + 1)
				break;
			if (split_str[left_bnd] != split_str[right_bnd])
				break;
			else
				palin_arr[(left_bnd + 1) >> 1][(right_bnd - 1) >> 1] = 1;
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
		scanf("%s", input_str + 1);
		int len = strlen(input_str + 1);
		//pre_calcu(input_str, len);
		memset(palin_arr, -1, sizeof(palin_arr));
		d[0] = 0;
		for (int i = 1; i <= len; i++)
			d[i] = i;
		for (int i = 1; i <= len; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (is_palin(j + 1, i))
					d[i] = min(d[i], d[j] + 1);
			}
		}
		printf("%d\n", d[len]);
	}
	return 0;
}