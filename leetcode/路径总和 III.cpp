//路径总和 III
//https://leetcode-cn.com/problems/path-sum-iii/
//树形 DP（选择节点类，DFS）
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

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
	int dfs(TreeNode *u, int target, bool contains_u)
	{
		assert(u != nullptr);
		if (contains_u)
		{
			int ans = 0;
			if (u->val == target)
				ans += 1;
			if (u->left != nullptr)
				ans += dfs(u->left, target - u->val, true);
			if (u->right!= nullptr)
				ans += dfs(u->right, target - u->val, true);
			return ans;
		}
		else
		{
			int ans = 0;
			if (u->left != nullptr)
			{
				ans += dfs(u->left, target, true);
				ans += dfs(u->left, target, false);
			}
			if (u->right != nullptr)
			{
				ans += dfs(u->right, target, true);
				ans += dfs(u->right, target, false);
			}
			return ans;
		}
	}

	int pathSum(TreeNode *root, int targetSum)
	{
		if (root == nullptr)
			return 0;
		return dfs(root, targetSum, true) + dfs(root, targetSum, false);
	}
};

int main()
{
	auto sol = new Solution();
	return 0;
}
