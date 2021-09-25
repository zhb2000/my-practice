#include<iostream>
#include<cstdio>
#include<unordered_map>
#include<unordered_set>
#include<vector>
using namespace std;

const int maxn = int(1e3 + 3);
unordered_set<int> G[maxn];//followed

int n, m;
int t;

bool is_hong(int u)
{
	if (int(G[u].size()) >= t)
	{
		for (int v : G[u])
			if (G[v].count(u) > 0)
				return false;
		return true;
	}
	else
		return false;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif // LOCAL

	cin >> n >> m >> t;
	for (int c = 1; c <= m; c++)
	{
		int u, v;
		cin >> u >> v;
		G[u].insert(v);
	}
	vector<int> ans;
	for (int u = 1; u <= n; u++)
	{
		if (is_hong(u))
			ans.push_back(u);
	}
	if (ans.empty())
		cout << "None";
	else
	{
		bool isfirst = true;
		for (int u : ans)
		{
			if (isfirst)
				isfirst = false;
			else
				cout << " ";
			cout << u;
		}
	}

	return 0;
}
