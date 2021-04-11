# P2014 [CTSC1997]选课
# 树形背包 O(n^3) 做法
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


MAXN = 300 + 3
MAXM = 300 + 3
f = [[-1 for j in range(MAXM)] for i in range(MAXN)]
goal = [0 for _ in range(MAXN)]
G: List[List[int]] = [[] for _ in range(MAXN)]
m = 0


def dfs(u: int):
    f[u][0] = 0
    f[u][1] = goal[u]
    for v in G[u]:
        dfs(v)
        for k in range(m + 1, 1 - 1, -1):
            for a in range(0, k):
                if f[v][a] == -1 or f[u][k - a] == -1:
                    continue
                temp = f[v][a] + f[u][k - a]
                f[u][k] = max(f[u][k], temp)


def main():
    global m
    n, m = read_ints()
    for v in range(1, n + 1):
        u, a = read_ints()
        G[u].append(v)
        goal[v] = a
    dfs(0)
    print(f[0][m + 1])


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
