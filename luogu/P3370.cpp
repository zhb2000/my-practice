// P3370 【模板】字符串哈希 拉链式哈希

#define LOCAL

#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

const int maxlen = 1500 + 3;
const int maxn = 10000 + 3;
typedef int PtrToNode;
struct Node
{
	char str[maxlen];
	PtrToNode next;
};
Node nodes[maxn];
int pos_nodes;

const int table_size = 10000019;
PtrToNode hash_table[table_size];

int new_node();
int str_hash(const char *str);
bool try_to_insert(const char *str);
bool check(int hash_code, const char *str);

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	pos_nodes = 1;
	int cnt = 0;
	int n;
	scanf("%d", &n);
	char str[maxlen];
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", str);
		if (try_to_insert(str))
			cnt++;
	}
	printf("%d", cnt);
	return 0;
}

int new_node()
{
	return pos_nodes++;
}

int str_hash(const char * str)
{
	int hash_code = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		hash_code = ((hash_code << 6) + str[i]) % table_size;
	}
	return hash_code;
}

bool try_to_insert(const char * str)
{
	int hash_code = str_hash(str);
	if (check(hash_code, str))
	{
		PtrToNode pn = new_node();
		strcpy(nodes[pn].str, str);
		nodes[pn].next = hash_table[hash_code];
		hash_table[hash_code] = pn;
		return true;
	}
	else
		return false;
}

bool check(int hash_code, const char *str)
{
	int p = hash_table[hash_code];
	while (p != 0)
	{
		if (strcmp(nodes[p].str, str) == 0)
			return false;
		p = nodes[p].next;
	}
	return true;
}