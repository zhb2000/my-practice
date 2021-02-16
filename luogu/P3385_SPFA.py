# P3385 【模板】负环
# SPFA
import math
from math import sqrt, ceil, floor, fabs, sin, cos
import sys
from typing import List, Tuple, Set, Dict, Iterable
from collections import deque

LOCAL, DEBUG = False, False


# LOCAL = True
# DEBUG = True

def read_strs() -> List[str]:
    return input().strip().split(' ')


def read_ints() -> List[int]:
    return list(map(int, read_strs()))


INF = int(1e9)


class Edge:
    def __init__(self, u: int = 0, v: int = 0, w: int = 0):
        self.fro = u
        self.to = v
        self.weight = w


MAXN = int(2e3 + 5)
dist = [INF for _ in range(MAXN)]
G = [[] for _ in range(MAXN)]
cnt = [0 for _ in range(MAXN)]
is_in_queue = [False for _ in range(MAXN)]


def relax(e: Edge) -> bool:
    u = e.fro
    v = e.to
    w = e.weight
    if dist[u] + w < dist[v]:
        dist[v] = dist[u] + w
        return True
    else:
        return False


def spfa(n: int) -> bool:
    dist[1] = 0
    q = deque()
    q.append(1)
    is_in_queue[1] = True
    while len(q) != 0:
        u = q.popleft()
        is_in_queue[u] = False
        for e in G[u]:
            v = e.to
            if relax(e):
                cnt[v] += 1
                if cnt[v] >= n:
                    return False
                if not is_in_queue[v]:
                    q.append(v)
                    is_in_queue[v] = True
    return True


def add_edge(u: int, v: int, w: int):
    G[u].append(Edge(u, v, w))


def add_bi_edge(u: int, v: int, w: int):
    add_edge(u, v, w)
    add_edge(v, u, w)


def init(n: int):
    for node in range(1, n + 1):
        G[node].clear()
        dist[node] = INF
        cnt[node] = 0
        is_in_queue[node] = False


def main():
    t = int(input())
    for case in range(t):
        n, m = read_ints()
        init(n)
        for _ in range(m):
            u, v, w = read_ints()
            if w >= 0:
                add_bi_edge(u, v, w)
            else:
                add_edge(u, v, w)
        if not spfa(n):
            print('YES')
        else:
            print('NO')


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
