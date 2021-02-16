//二叉搜索树节点最小距离
//https://leetcode-cn.com/problems/minimum-distance-between-bst-nodes/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

using namespace std;
using ll = long long;
const ll INF = ll(1e10);

class Solution 
{
public:
    vector<int> vals;
    
    void dfs(TreeNode *u)
    {
        if (u == nullptr)
            return;
        vals.push_back(u->val);
        dfs(u->left);
        dfs(u->right);
    }
    
    int minDiffInBST(TreeNode* root) 
    {
        dfs(root);
        sort(vals.begin(), vals.end());
        ll min_diff = INF;
        for (int i = 0; i + 1 < int(vals.size()); i++)
        {
            ll diff = vals[i + 1] - vals[i];
            min_diff = min(min_diff, diff);
        }
        return int(min_diff);
    }
};
