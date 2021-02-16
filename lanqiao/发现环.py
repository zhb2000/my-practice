import math
import sys
from typing import List, Tuple, Set, Dict, Iterable
from math import sqrt, ceil, floor, fabs, sin, cos

LOCAL, DEBUG = False, False


# LOCAL = True
# DEBUG = True

def read_strs() -> List[str]:
    return input().split(' ')


def read_ints() -> List[int]:
    return list(map(int, read_strs()))


maxn = 100000 + 5
G: List[List[int]] = [[] for _ in range(maxn)]
vis = [0 for _ in range(maxn)]
father = [0 for _ in range(maxn)]
result: List[int] = []


def dfs(u: int, fa: int) -> bool:
    father[u] = fa
    vis[u] = -1
    for v in G[u]:
        if v != fa:
            if vis[v] < 0:
                assert len(result) == 0
                p = u
                while True:
                    result.append(p)
                    if p == v:
                        break
                    p = father[p]
            elif vis[v] == 0:
                if not dfs(v, u):
                    return False
    vis[u] = 1
    return True


def add_bi_edge(u: int, v: int):
    G[u].append(v)
    G[v].append(u)


def print_result(res: Iterable[int]):
    is_first = True
    for u in res:
        if is_first:
            is_first = False
        else:
            print(' ', end='')
        print(u, end='')


def main():
    n = int(input())
    for _ in range(n):
        u, v = read_ints()
        add_bi_edge(u, v)
    dfs(1, -1)
    result.sort()
    print_result(result)


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
