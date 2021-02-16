//【模板】并查集
#include<iostream>
#include<cstdio>
#include<string>
#include<functional>
#include<algorithm>
#include<array>
#include<vector>
#include<map>
#include<utility>
#include<tuple>
#include<cstring>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
template <int maxNum>
class UnionFindSet
{
private:
	int fa_[maxNum];
	int size_[maxNum];
	int find(int x)
	{
		if (x != fa_[x])
			fa_[x] = find(fa_[x]);
		return fa_[x];
	}

public:
	UnionFindSet()
	{
		this->reset();
	}
	void reset()
	{
		for (int x = 0; x < maxNum; x++)
		{
			fa_[x] = x;
			size_[x] = 1;
		}
	}
	void union2(int x, int y)
	{
		int xx = find(x);
		int yy = find(y);
		if (xx == yy)
			return;
		if (size_[xx] < size_[yy])
			swap(xx, yy);
		fa_[yy] = xx;
		size_[xx] += size_[yy];
	}
	bool in_same(int x, int y)
	{
		return find(x) == find(y);
	}
};

const int maxn = 10000 + 5;
UnionFindSet<maxn> ufset;

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	int n, m;
	scanf("%d%d", &n, &m);
	for (int c = 1; c <= m; c++)
	{
		int z, x, y;
		scanf("%d%d%d", &z, &x, &y);
		if (z == 1)
			ufset.union2(x, y);
		else if (z == 2)
		{
			if (ufset.in_same(x, y))
				puts("Y");
			else
				puts("N");
		}
	}



#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}