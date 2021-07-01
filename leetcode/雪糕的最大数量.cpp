//雪糕的最大数量
//https://leetcode-cn.com/classic/problems/maximum-ice-cream-bars/description/
//贪心、排序
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<stack>
#include<deque>
#include<utility>
#include<cmath>

using namespace std;

class Solution
{
public:
	int maxIceCream(vector<int> &costs, int coins)
	{
		sort(costs.begin(), costs.end());
		int ans = 0;
		for (int x : costs)
		{
			if (coins - x < 0)
				break;
			coins -= x;
			ans++;
		}
		return ans;
	}
};

int main()
{
	vector<int> costs;
	int coins;
	costs = { 1,3,2,4,1 };
	coins = 7;
	costs = { 10,6,8,7,7,8 };
	coins = 5;
	costs = { 1,6,3,1,2,5 };
	coins = 20;
	auto sol = new Solution();
	cout << sol->maxIceCream(costs, coins) << endl;
	return 0;
}