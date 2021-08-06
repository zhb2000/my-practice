//计算右侧小于当前元素的个数
//https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/
//平衡二叉树（替罪羊树）
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

struct SgTree
{
    static const int maxn = int(1e5 + 3);
    struct Node
    {
        int num; //存储的数字
        int cnt = 1; //重复次数
        int lch = 0;
        int rch = 0;
        int num_size = 1; //子树的大小（考虑重复数字）
        int tree_size = 1; //子树的大小（不考虑重复数字，只考虑节点个数）
    };
    //num_size 用来求排名
    //tree_size 用来判断是否重构

    const double balance_alpha = 0.7; //平衡比例系数
    vector<Node> ns{ maxn };
    int nxt_new = 1;
    int new_node() { return nxt_new++; }
    vector<int> flat_vec; //临时数组，存放拉平后的节点

    int tree_size(int u) { return (u != 0) ? ns[u].tree_size : 0; }

    int num_size(int u) { return(u != 0) ? ns[u].num_size : 0; }

    //用临时数组 [l, r] 中的节点建一棵树
    //return: 树根
    int rebuild_from_vec(int l, int r)
    {
        if (r < l)
            return 0;
        int m = (l + r) / 2;
        int root = flat_vec[m]; //中间的节点作为根节点
        //递归对左右子区间建树
        ns[root].lch = rebuild_from_vec(l, m - 1);
        ns[root].rch = rebuild_from_vec(m + 1, r);
        ns[root].num_size = num_size(ns[root].lch) + ns[root].cnt + num_size(ns[root].rch);
        ns[root].tree_size = tree_size(ns[root].lch) + 1 + tree_size(ns[root].rch);
        return root;
    }

    //中序遍历以 u 为根的子树
    template<class Fn>
    void inorder(int u, const Fn &f)
    {
        if (u == 0)
            return;
        inorder(ns[u].lch, f);
        f(u);
        inorder(ns[u].rch, f);
    }

    //尝试重构以 u 为根的子树
    void try_rebuild(int &u)
    {
        assert(u != 0);
        int lts = tree_size(ns[u].lch);
        int rts = tree_size(ns[u].rch);
        if (double(max(lts, rts)) / ns[u].tree_size > balance_alpha)
        {
            flat_vec.clear();
            inorder(u, [this](int node)
            {
                if (node != 0 && ns[node].cnt > 0) // 重构时删除 cnt 为 0 的点
                    flat_vec.push_back(node);
            });
            u = rebuild_from_vec(0, int(flat_vec.size()) - 1);
        }
    }

    //插入
    void u_insert(int &u, int num)
    {
        if (u == 0) //插入时，到达空结点则新建节点
        {
            u = new_node();
            ns[u].num = num;
            return;
        }

        if (num == ns[u].num)
            ns[u].cnt++;
        else if (num < ns[u].num)
            u_insert(ns[u].lch, num);
        else
            u_insert(ns[u].rch, num);
        ns[u].num_size++;
        ns[u].tree_size = tree_size(ns[u].lch) + 1 + tree_size(ns[u].rch);
        try_rebuild(u);
    }

    //删除
    void u_remove(int u, int num)
    {
        assert(u != 0);
        if (num == ns[u].num)
        {
            assert(ns[u].cnt > 0);
            ns[u].cnt--; //懒惰删除
        }
        else if (num < ns[u].num)
            u_remove(ns[u].lch, num);
        else
            u_remove(ns[u].rch, num);
        ns[u].num_size--;
    }

    //查询元素的排名（元素必须在树中）
    int rank_of_num(int u, int num)
    {
        assert(u != 0);
        int lns = num_size(ns[u].lch);
        if (num == ns[u].num)
        {
            assert(ns[u].cnt > 0);
            return lns + 1;
        }
        else if (num < ns[u].num)
            return rank_of_num(ns[u].lch, num);
        else
            return lns + ns[u].cnt + rank_of_num(ns[u].rch, num);
    }

    int root = 0; //整棵树的树根

    //查询元素的排名（元素可以不在树中）
    int get_rank_of_num(int num)
    {
        u_insert(root, num);
        int rk = rank_of_num(root, num);
        u_remove(root, num);
        return rk;
    }

    void insert(int num) { u_insert(root, num); }
};

class Solution
{
public:
    vector<int> countSmaller(vector<int> &nums)
    {
        int n = int(nums.size());
        SgTree *tree = new SgTree();
        auto result = vector<int>(n);
        for (int i = n - 1; i >= 0; i--)
        {
            result[i] = tree->get_rank_of_num(nums[i]) - 1;
            tree->insert(nums[i]);
        }
        delete tree;
        return result;
    }
};

int main()
{
	auto sol = new Solution();
    vector<int> nums = { 5,2,6,1 };
    vector<int> result = sol->countSmaller(nums);
    for (int x : result)
        cout << x << ' ';
	return 0;
}
