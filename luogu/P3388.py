# P3388 【模板】割点（割顶）
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


MAXN = int(2e4 + 5)
G = [[] for _ in range(MAXN)]
num = [0 for _ in range(MAXN)]
low = [0 for _ in range(MAXN)]
vis = [False for _ in range(MAXN)]
dfscnt = 0
cut_list = []


def tarjan(u: int, father: int):
    global dfscnt
    dfscnt += 1
    num[u] = dfscnt
    low[u] = dfscnt
    vis[u] = True
    is_cut = False
    child = 0
    for v in G[u]:
        if v != father:
            if not vis[v]:
                child += 1
                tarjan(v, u)
                low[u] = min(low[u], low[v])
                if father != -1 and low[v] >= num[u]:
                    is_cut = True
            else:
                low[u] = min(low[u], num[v])
    if father == -1 and child >= 2:
        is_cut = True
    if is_cut:
        cut_list.append(u)


def add_bi_edge(u: int, v: int):
    G[u].append(v)
    G[v].append(u)


def print_ans():
    print(len(cut_list))
    isfirst = True
    for u in cut_list:
        if isfirst:
            isfirst = False
        else:
            print(' ', end='')
        print(u, end='')


def main():
    n, m = read_ints()
    for _ in range(m):
        u, v = read_ints()
        add_bi_edge(u, v)
    for u in range(1, n + 1):
        if not vis[u]:
            global dfscnt
            dfscnt = 0
            tarjan(u, -1)
    cut_list.sort()
    print_ans()


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
