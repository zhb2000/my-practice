//合法二叉搜索树
//https://leetcode-cn.com/problems/legal-binary-search-tree-lcci/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

using ll = long long;
const ll INF = ll(1e10);

class Solution
{
public:
    bool isValidBST(TreeNode* root)
    {
        return isvalid(root, -INF, INF);
    }
    
    bool isvalid(TreeNode *u, ll min, ll max)
    {
        if(u == nullptr)
            return true;
        if(min < u->val && u->val < max)
        {
            if(!isvalid(u->left, min, u->val))
                return false;
            if(!isvalid(u->right, u->val, max))
                return false;
            return true;
        }
        else
            return false;
    }
};
