// P3375 【模板】KMP字符串匹配

#define LOCAL

#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

//-1表示长度为0不存在，0表示长度为1
void calcu_next(char *str, int *next, int len)
{
	next[0] = -1;
	int k = -1;//k是左边格子可利用的next值
	//p是游标，计算下标p位置的next值
	for (int p = 1; p < len; p++)
	{
		//无法多一个相同字符，则向左回溯
		while (k > -1 && str[k + 1] != str[p])
			k = next[k];
		//多一个相同字符，就是之前的长度加1
		if (str[k + 1] == str[p])
			k++;
		next[p] = k;//最终结果赋值
	}
}

int kmp(char *str, int slen, char *pstr, int plen)
{
	int *pnext = new int[plen];//模式串的next数组
	calcu_next(pstr, pnext, plen);
	int k = -1;//模式串已匹配部分末尾字符的位置
	for (int i = 0; i < slen; i++)//i是str中的游标
	{
		//有部分匹配但无法多一个相同字符，则向左回溯
		while (k > -1 && pstr[k + 1] != str[i])
			k = pnext[k];
		//多一个相同字符，之前的k加1
		if (pstr[k + 1] == str[i])
			k++;
		if (k == plen - 1)//模式串末尾，返回结果
		{
			printf("%d\n", i - plen + 1 + 1);
			k = -1;
			i = i - plen + 1;
		}
	}

	for (int i = 0; i < plen; i++)
	{
		printf("%d", pnext[i] + 1);
		if (i != plen - 1)
			printf(" ");
	}
	delete[] pnext;
	return -1;//匹配失败
}

char str[1000000 + 3];
char pstr[1000000 + 3];

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	scanf("%s", str);
	scanf("%s", pstr);
	kmp(str, strlen(str), pstr, strlen(pstr));
	return 0;
}