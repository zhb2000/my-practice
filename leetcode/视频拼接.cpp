//视频拼接
//https://leetcode-cn.com/problems/video-stitching/
//排序、贪心，线段区间覆盖问题
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
#include<numeric>
using namespace std;
template<class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
	os << "[";
	bool isfirst = true;
	for (const auto &x : v)
	{
		if (isfirst)
			isfirst = false;
		else
			os << ", ";
		os << x;
	}
	os << "]";
	return os;
}

//按左端点排序，选左端点在当前线段范围内的右端点最右的线段作为下一个线段
class Solution
{
public:
	int videoStitching(vector<vector<int>> &clips, int time)
	{
		int n = int(clips.size());
		sort(clips.begin(), clips.end(), [](const auto &a, const auto &b)
		{
			if (a[0] == b[0])
				return a[1] > b[1];
			return a[0] < b[0];
		});
		if (clips[0][0] > 0)
			return -1;
		int cur_end = clips[0][1];
		int right = cur_end;
		int select = -1;
		int tot = 1;
		for (int i = 1; i < n && cur_end < time; i++)
		{
			if (clips[i][0] <= cur_end)
			{
				if (clips[i][1] > right)
				{
					right = clips[i][1];
					select = i;
				}
			}
			else
			{
				if (select == -1)
					return -1;
				cur_end = clips[select][1];
				right = cur_end;
				select = -1;
				tot++;
				
				i -= 1;
			}
		}
		if (select != -1)
		{
			cur_end = clips[select][1];
			tot++;
		}
		if (cur_end < time)
			return -1;
		return tot;
	}
};

int main()
{
	auto sol = new Solution();
	vector<vector<int>> clips;
	int time;

	clips = {{0, 2}, {4, 6}, {8, 10}, {1, 9}, {1, 5}, {5, 9}};
	time = 10;
	cout << sol->videoStitching(clips, time) << endl;//3
	
	clips = {{0, 1}, {1, 2}};
	time = 5;
	cout << sol->videoStitching(clips, time) << endl;//-1

	clips = {{0, 1}, {6, 8}, {0, 2}, {5, 6}, {0, 4}, {0, 3}, {6, 7}, {1, 3}, {4, 7}, {1, 4}, {2, 5}, {2, 6}, {3, 4}, {4, 5}, {5, 7}, {6, 9}};
	time = 9;
	cout << sol->videoStitching(clips, time) << endl;//3


	clips = {{0, 4}, {2, 8}};
	time = 5;
	cout << sol->videoStitching(clips, time) << endl;//2

	clips = {{0, 2}, {1, 6}, {3, 10}};
	time = 10;
	cout << sol->videoStitching(clips, time) << endl;//3

	delete sol;
	return 0;
}
