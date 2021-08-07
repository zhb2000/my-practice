//天际线问题
//https://leetcode-cn.com/problems/the-skyline-problem/
//扫描线、优先队列维护当前最大高度
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
#include<cassert>
using namespace std;

class Solution
{
public:
	struct Line
	{
		int buiding;
		int x;
		int h;
		bool enter;
		bool operator<(const Line &other) const
		{
			return x < other.x;
		}
	};

	struct Building
	{
		int id;
		int h;
		bool operator<(const Building &other) const
		{
			return h < other.h;
		}
	};

	vector<vector<int>> getSkyline(vector<vector<int>> &buildings)
	{
		int n = int(buildings.size());
		vector<Line> lines;
		auto building_in_pq = vector<bool>(n);
		for (int i = 0; i < n; i++)
		{
			int l = buildings[i][0];
			int r = buildings[i][1];
			int h = buildings[i][2];
			lines.push_back({ i, l, h, true });
			lines.push_back({ i, r, h, false });
		}
		sort(lines.begin(), lines.end());
		priority_queue<Building> pq;
		vector<vector<int>> ans;
		int i = 0; int lsz = int(lines.size());
		while (i < lsz)
		{
			int old_maxh = get_maxh(pq, building_in_pq);
			int x = lines[i].x;
			while (i < lsz && lines[i].x == x) //handle all events of x
			{
				if (lines[i].enter)
				{
					pq.push({ lines[i].buiding, lines[i].h });
					building_in_pq[lines[i].buiding] = true;
				}
				else
					building_in_pq[lines[i].buiding] = false;
				i++;
			}
			int new_maxh = get_maxh(pq, building_in_pq);
			if (new_maxh != old_maxh)
				ans.push_back({ x, new_maxh });

		}
		return ans;
	}

	int get_maxh(priority_queue<Building> &pq, const vector<bool> &building_in_pq)
	{
		while (!pq.empty() && !building_in_pq[pq.top().id])
			pq.pop(); //pop all removed
		return !pq.empty() ? pq.top().h : 0;
	}
};

void print_ans(const vector<vector<int>> &ans)
{
	for (const auto &p : ans)
		cout << '(' << p[0] << ',' << p[1] << ") ";
	cout << endl;
}

int main()
{
	auto sol = new Solution();
	vector<vector<int>> buildings;
	buildings = { {2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8} };
	//buildings = { {0,2,3},{2,5,3} };
	auto ans = sol->getSkyline(buildings);
	print_ans(ans);
	return 0;
}
