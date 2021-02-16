# P3387 【模板】缩点
# tarjan 求强连通分量、缩点
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
G = [[] for _ in range(MAXN)]
n_vis = [False for _ in range(MAXN)]
n_in_stack = [False for _ in range(MAXN)]
n_val = [0 for _ in range(MAXN)]
n_belong = [0 for _ in range(MAXN)]
n_dfn = [0 for _ in range(MAXN)]
n_low = [0 for _ in range(MAXN)]
st = []
block_roots = []
block_val_sum = [0 for _ in range(MAXN)]
dp_arr = [-1 for _ in range(MAXN)]
G2_in = [set() for _ in range(MAXN)]
timer = 0


def tarjan(u: int):
    global timer
    n_vis[u] = True
    st.append(u)
    n_in_stack[u] = True
    timer += 1
    n_dfn[u] = timer
    n_low[u] = timer
    for v in G[u]:
        if not n_vis[v]:
            tarjan(v)
            n_low[u] = min(n_low[u], n_low[v])
        elif n_in_stack[v]:
            n_low[u] = min(n_low[u], n_dfn[v])
    if n_dfn[u] == n_low[u]:
        block_roots.append(u)
        block_val_sum[u] = 0
        while True:
            node = st.pop()
            n_in_stack[node] = False
            n_belong[node] = u
            block_val_sum[u] += n_val[node]
            if node == u:
                break


def dp(block: int) -> int:
    if dp_arr[block] != -1:
        return dp_arr[block]
    else:
        pre_max = 0
        for u in G2_in[block]:
            pre_max = max(pre_max, dp(u))
        dp_arr[block] = pre_max + block_val_sum[block]
        return dp_arr[block]


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
                G2_in[blv].add(blu)
    ans = 0
    for block in block_roots:
        ans = max(ans, dp(block))
    return ans


def add_edge(u: int, v: int):
    G[u].append(v)


def main():
    n, m = read_ints()
    values = read_ints()
    assert len(values) == n
    for i, v in enumerate(values):
        n_val[i + 1] = v
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
