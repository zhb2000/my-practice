# P2341 [USACO03FALL][HAOI2006]受欢迎的牛 G
# 缩点
import math
import sys
import collections
import random
import heapq
from math import sqrt, ceil, floor, fabs, sin, cos
from typing import List, Tuple, Set, Dict, Iterable
from collections import deque

LOCAL, DEBUG = False, False


# LOCAL = True
# DEBUG = True


def read_strs() -> List[str]:
    return input().strip().split(' ')


def read_ints() -> List[int]:
    return list(map(int, read_strs()))


MAXN = int(1e4 + 5)
G = [[] for _ in range(MAXN)]  # G: int[][MAXN]
n_dfn = [0 for _ in range(MAXN)]  # dfn: int[MAXN]
n_low = [0 for _ in range(MAXN)]  # low: int[MAXN]
n_vis = [False for _ in range(MAXN)]  # vis: bool[MAXN]
n_in_stack = [False for _ in range(MAXN)]  # in_stack: bool[MAXN]
n_belong = [0 for _ in range(MAXN)]  # belong: int[MAXN]
st = []
timer = 0

MAXB = MAXN
blocks = []  # blocks: int[]
G2 = [set() for _ in range(MAXB)]  # set<int>[MAXB]
b_num = [0 for _ in range(MAXB)]  # num: int[MAXB]


def tarjan(u: int):
    global timer
    timer += 1
    n_dfn[u] = timer
    n_low[u] = timer
    n_vis[u] = True
    st.append(u)
    n_in_stack[u] = True
    for v in G[u]:
        if not n_vis[v]:
            tarjan(v)
            n_low[u] = min(n_low[u], n_low[v])
        elif n_in_stack[v]:
            n_low[u] = min(n_low[u], n_dfn[v])
    if n_dfn[u] == n_low[u]:
        blocks.append(u)
        while True:
            node = st.pop()
            n_in_stack[node] = False
            n_belong[node] = u
            b_num[u] += 1
            if node == u:
                break


def solve(n: int) -> int:
    # tarjan
    for u in range(1, n + 1):
        if not n_vis[u]:
            tarjan(u)
    # build DAG
    for u in range(1, n + 1):
        blu = n_belong[u]
        for v in G[u]:
            blv = n_belong[v]
            if blv != blu:
                G2[blu].add(blv)
    block_num = len(blocks)
    ans = 0
    has_zero_out = False
    for block in blocks:
        if len(G2[block]) == 0:
            if has_zero_out:
                return 0
            else:
                has_zero_out = True
                ans = b_num[block]
    return ans


def add_edge(u: int, v: int):
    G[u].append(v)


def main():
    n, m = read_ints()
    for _ in range(m):
        u, v = read_ints()
        add_edge(u, v)
    print(solve(n), end='')


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
