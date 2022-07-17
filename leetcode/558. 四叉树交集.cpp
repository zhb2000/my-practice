// 558. 四叉树交集
// https://leetcode.cn/problems/logical-or-of-two-binary-grids-represented-as-quad-trees/
// 递归、分治
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <deque>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

// Definition for a QuadTree node.
class Node
{
public:
    bool val;
    bool isLeaf;
    Node *topLeft;
    Node *topRight;
    Node *bottomLeft;
    Node *bottomRight;

    Node()
    {
        val = false;
        isLeaf = false;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    Node(bool _val, bool _isLeaf)
    {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    Node(bool _val, bool _isLeaf, Node *_topLeft, Node *_topRight, Node *_bottomLeft, Node *_bottomRight)
    {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution
{
public:
    Node *intersect(Node *q1, Node *q2)
    {
        if (q1->isLeaf)
            return q1->val ? new Node(true, true) : q2;
        else if (q2->isLeaf)
            return q2->val ? new Node(true, true) : q1;
        else
        {
            Node *tl = intersect(q1->topLeft, q2->topLeft),
                 *tr = intersect(q1->topRight, q2->topRight),
                 *bl = intersect(q1->bottomLeft, q2->bottomLeft),
                 *br = intersect(q1->bottomRight, q2->bottomRight);
            return (tl->isLeaf && tr->isLeaf && bl->isLeaf && br->isLeaf
                    && tl->val == tr->val && tl->val == bl->val && tl->val == br->val)
                       ? new Node(tl->val, true)
                       : new Node(false, false, tl, tr, bl, br);
        }
    }
};

template <class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << '[';
    bool first = true;
    for (const T &x : v)
    {
        if (first)
            first = false;
        else
            os << ", ";
        os << x;
    }
    os << ']';
    return os;
}

int main()
{
    auto *solution = new Solution();

    delete solution;
    return 0;
}
