//850. 矩形面积 II
//https://leetcode-cn.com/classic/problems/rectangle-area-ii/description/
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<functional>
#include<algorithm>
#include<vector>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<stack>
#include<queue>
#include<deque>
#include<utility>
#include<tuple>
#include<bitset>
#include<cassert>
#include<cctype>
#include<cmath>
#include<ctime>
using namespace std;

struct Solution
{
	using ll = long long;
	static const int MOD = int(1e9 + 7);
	static const int MAXN = 200 + 5;

	vector<int> y_vec;
	int y_vec_len;
	int piece_to_y_down(int piece) { return y_vec[piece - 1]; }
	int piece_to_y_up(int piece) { return y_vec[piece]; }
	int get_piece_by_y_down(int y_down)
	{
		int index = lower_bound(y_vec.begin(), y_vec.begin() + y_vec_len, y_down) - y_vec.begin();
		return index + 1;
	}
	int get_piece_by_y_up(int y_up)
	{
		int index = lower_bound(y_vec.begin(), y_vec.begin() + y_vec_len, y_up) - y_vec.begin();
		return index;
	}

	// SegTree begin
	static int lch(int u) { return u * 2; }
	static int rch(int u) { return u * 2 + 1; }
	int cover[MAXN * 4];
	ll sum[MAXN * 4];

	void maintain(int u, int l, int r)
	{
		assert(u >= 1);
		assert(1 <= l && l <= r && r <= y_vec_len - 1);
		if (cover[u] > 0)
		{
			int y_up = piece_to_y_up(r);
			int y_down = piece_to_y_down(l);
			assert(y_down < y_up);
			sum[u] = y_up - y_down;
		}
		else // cover[u] == 0
		{
			if (l == r) // u is a leaf and u is not covered
				sum[u] = 0;
			else
				sum[u] = sum[lch(u)] + sum[rch(u)];
		}
	}

	void update(int ul, int ur, int delta, int u, int l, int r)
	{
		assert(u >= 1);
		assert(1 <= ul && ul <= ur && ur <= y_vec_len - 1);
		assert(1 <= l && l <= r && r <= y_vec_len - 1);
		if (ul <= l && r <= ur)
		{
			cover[u] += delta;
			maintain(u, l, r);
			return;
		}
		assert(l < r); // u is not a leaf
		int m = (l + r) / 2;
		if (ul <= m)
			update(ul, ur, delta, lch(u), l, m);
		if (m + 1 <= ur)
			update(ul, ur, delta, rch(u), m + 1, r);
		maintain(u, l, r);
	}
	//SegTree end

	struct Edge
	{
		int x, y_up, y_down, delta;
		bool operator<(const Edge &other) const
		{
			return x < other.x;
		}
	};

	vector<Edge> edges;

	int rectangleArea(vector<vector<int>> &rectangles)
	{
		memset(sum, 0, sizeof(sum));
		memset(cover, 0, sizeof(cover));

		for (const vector<int> &rectangle : rectangles)
		{
			int x_left = rectangle[0];
			int y_down = rectangle[1];
			int x_right = rectangle[2];
			int y_up = rectangle[3];
			edges.push_back({ x_left,y_up,y_down,1 });
			edges.push_back({ x_right,y_up,y_down,-1 });
			y_vec.push_back(y_down);
			y_vec.push_back(y_up);
		}
		sort(edges.begin(), edges.end());

		sort(y_vec.begin(), y_vec.end());
		y_vec_len = unique(y_vec.begin(), y_vec.end()) - y_vec.begin();

		ll ans = 0;
		int last_x = 0;
		for (const Edge &e : edges)
		{
			ll scan_len = sum[1];
			ans = (ans + (scan_len * (e.x - last_x)) % MOD) % MOD;
			int ul_piece = get_piece_by_y_down(e.y_down);
			int ur_piece = get_piece_by_y_up(e.y_up);
			assert(ul_piece >= 1);
			assert(ur_piece <= y_vec_len);
			assert(ul_piece <= ur_piece);
			update(ul_piece, ur_piece, e.delta, 1, 1, y_vec_len - 1);
			last_x = e.x;
		}

		return int(ans);
	}
};

int main()
{
	auto solution = new Solution();
	vector<vector<int>> rectangles;
	rectangles = { {0, 0, 2, 2}, {1, 0, 2, 3}, {1, 0, 3, 1} };
	//rectangles = { {0, 0, 1000000000, 1000000000} };
	//rectangles = { {0, 0, 1000000000, 1000000000}, {0, 0, 1000000000, 1000000000} };
	cout << solution->rectangleArea(rectangles) << '\n';
	delete solution;

	return 0;
}
