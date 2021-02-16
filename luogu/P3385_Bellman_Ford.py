# P3385 【模板】负环
# Bellman-Ford
import math
import sys
from typing import List, Tuple, Set, Dict, Iterable
from math import sqrt, ceil, floor, fabs, sin, cos

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
edges = []
vis = [False for _ in range(MAXN)]
dist = [INF for _ in range(MAXN)]
G = [[] for _ in range(MAXN)]
connect_set = set()


def relax(e: Edge) -> bool:
    u = e.fro
    v = e.to
    w = e.weight
    if dist[u] + w < dist[v]:
        dist[v] = dist[u] + w
        return True
    else:
        return False


def bellman_ford(n: int) -> bool:
    dist[1] = 0
    for _ in range(n - 1):
        for e in edges:
            relax(e)
    for e in edges:
        if relax(e):
            return False
    return True


def add_edge(u: int, v: int, w: int):
    G[u].append(Edge(u, v, w))


def add_bi_edge(u: int, v: int, w: int):
    add_edge(u, v, w)
    add_edge(v, u, w)


def init(n: int):
    edges.clear()
    connect_set.clear()
    for node in range(1, n + 1):
        vis[node] = False
        G[node].clear()
        dist[node] = INF


def dfs_connected(u: int):
    vis[u] = True
    connect_set.add(u)
    for oute in G[u]:
        v = oute.to
        if not vis[v]:
            dfs_connected(v)


def build_connected():
    dfs_connected(1)
    for node in connect_set:
        for e in G[node]:
            edges.append(e)


def main():
    T = int(input())
    for _ in range(T):
        n, m = read_ints()
        init(n)
        for _ in range(m):
            u, v, w = read_ints()
            if w >= 0:
                add_bi_edge(u, v, w)
            else:
                add_edge(u, v, w)
        build_connected()
        if not bellman_ford(n):
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
