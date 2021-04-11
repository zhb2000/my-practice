# P2015 二叉苹果树
# 树形 DP
import math
import sys
import collections
import random
import heapq
import bisect
import typing
from math import sqrt, ceil, floor, fabs, sin, cos
from typing import List, Tuple, Set, Dict, Iterable, Deque, TypeVar
from collections import deque
from bisect import bisect_left, bisect_right

LOCAL, DEBUG = False, False


# LOCAL = True
# DEBUG = True


def read_strs() -> List[str]:
    return input().split()


def read_ints() -> List[int]:
    return list(map(int, read_strs()))


def build_string(seq: Iterable[str]) -> str:
    return ''.join(seq)


MAXN = 100 + 3
node_num = [0 for _ in range(MAXN)]
lch = [-1 for _ in range(MAXN)]
rch = [-1 for _ in range(MAXN)]
fa_eval = [0 for _ in range(MAXN)]
f_arr = [[-1 for j in range(MAXN)] for i in range(MAXN)]
G: List[List[Tuple[int, int]]] = [[] for _ in range(MAXN)]


def dfs_to_tree(u: int, fa: int):
    es = list(filter(lambda p: p[0] != fa, G[u]))
    if len(es) == 0:
        return
    assert len(es) == 2
    lch[u] = es[0][0]
    fa_eval[lch[u]] = es[0][1]
    rch[u] = es[1][0]
    fa_eval[rch[u]] = es[1][1]
    dfs_to_tree(lch[u], u)
    dfs_to_tree(rch[u], u)


def get_edge_num(u: int) -> int:
    if lch[u] == -1:
        assert rch[u] == -1
        node_num[u] = 1
    else:
        node_num[u] = 1 + get_edge_num(lch[u]) + get_edge_num(rch[u])
    return node_num[u]


def f(u: int, n_num: int) -> int:
    if f_arr[u][n_num] != -1:
        return f_arr[u][n_num]
    assert node_num[u] >= n_num
    if lch[u] == -1:
        assert rch[u] == -1
        return 0
    child_sum = n_num - 1
    if child_sum == 0:
        return 0
    lmax = node_num[lch[u]]
    rmax = node_num[rch[u]]
    ans = 0
    for l in range(0, child_sum + 1):
        r = child_sum - l
        if l > lmax:
            break
        if r > rmax:
            continue
        lval = f(lch[u], l) + fa_eval[lch[u]] if l > 0 else 0
        rval = f(rch[u], r) + fa_eval[rch[u]] if r > 0 else 0
        temp = lval + rval
        ans = max(ans, temp)
    f_arr[u][n_num] = ans
    return ans


def main():
    n, q = read_ints()
    for _ in range(n - 1):
        a, b, val = read_ints()
        G[a].append((b, val))
        G[b].append((a, val))
    dfs_to_tree(1, -1)
    n_num = get_edge_num(1)
    assert n_num == n
    print(f(1, q + 1))


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
