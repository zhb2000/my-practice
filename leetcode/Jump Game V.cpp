//Jump Game V
//https://leetcode-cn.com/problems/jump-game-v/
//DP
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

class Solution
{
public:
	static const int maxn = 1000 + 3;
	int f_arr[maxn];

	int f(int i, const vector<int> &arr, int d)
	{
		if (f_arr[i] != -1)
			return f_arr[i];
		int n = int(arr.size());
		int nxt_ans = 0;
		for (int j = i + 1; j < n && j <= i + d; j++)
		{
			if (arr[j] >= arr[i])
				break;
			nxt_ans = max(nxt_ans, f(j, arr, d));
		}
		for (int j = i - 1; j >= 0 && j >= i - d; j--)
		{
			if (arr[j] >= arr[i])
				break;
			nxt_ans = max(nxt_ans, f(j, arr, d));
		}
		f_arr[i] = nxt_ans + 1;
		return nxt_ans + 1;
	}

	int maxJumps(vector<int> &arr, int d)
	{
		int n = int(arr.size());
		fill(f_arr, f_arr + n, -1);
		int ans = 1;
		for (int i = 0; i < n; i++)
			ans = max(ans, f(i, arr, d));
		return ans;
	}
};

int main()
{
	auto sol = new Solution();
	vector<int> arr; int d;

	arr = { 6,4,14,6,8,13,9,7,10,6,12 }; d = 2;
	cout << sol->maxJumps(arr, d) << endl;

	arr = { 3,3,3,3,3 }; d = 3;
	cout << sol->maxJumps(arr, d) << endl;

	arr = { 7,6,5,4,3,2,1 }; d = 1;
	cout << sol->maxJumps(arr, d) << endl;

	arr = { 7,1,7,1,7,1 }; d = 2;
	cout << sol->maxJumps(arr, d) << endl;

	arr = { 66 }; d = 1;
	cout << sol->maxJumps(arr, d) << endl;

	return 0;
}
