# 1483. 树节点的第 K 个祖先
# https://leetcode-cn.com/classic/problems/kth-ancestor-of-a-tree-node/description/
# LCA、倍增、二进制拆分
from typing import List, Dict, Set, Tuple, Iterable, Optional
import math
import random


class TreeAncestor:

    def __init__(self, n: int, parent: List[int]):
        self.fa = parent
        assert n == len(parent)
        self.depth = [-1 for _ in range(n)]
        self.fa = [[0 for i in range(31)] for u in range(n)]
        self.children = [[] for u in range(n)]
        for u in range(1, n):
            self.children[parent[u]].append(u)
        self.log2 = [0, 0]
        for i in range(2, n):
            self.log2.append(self.log2[i // 2] + 1)
        self.dfs(0, -1)

    def dfs(self, u: int, father: int):
        self.fa[u][0] = father
        self.depth[u] = 0 if father == -1 else self.depth[father] + 1
        for i in range(1, self.log2[self.depth[u]] + 1):
            self.fa[u][i] = self.fa[self.fa[u][i - 1]][i - 1]
        for v in self.children[u]:
            self.dfs(v, u)

    def getKthAncestor(self, node: int, k: int) -> int:
        if k == 0:
            return node
        if k > self.depth[node]:
            return -1
        d = self.depth[node] - k
        p = node
        while self.depth[p] > d:
            p = self.fa[p][self.log2[self.depth[p] - d]]
        assert self.depth[p] == d
        return p


if __name__ == '__main__':
    tree = TreeAncestor(7, [-1, 0, 0, 1, 1, 2, 2])
    qs = [[3, 1], [5, 2], [6, 3]]
    for node, k in qs:
        print(tree.getKthAncestor(node, k))
