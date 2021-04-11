import math
import sys
from typing import List, Tuple, Set, Dict
from math import sqrt, ceil, floor, fabs, sin, cos

LOCAL, DEBUG = False, False


#LOCAL = True
# DEBUG = True

def read_list() -> List[str]:
    return input().split(' ')


def read_int_list() -> List[int]:
    return list(map(int, read_list()))


MAXN = 300 + 5
INF = int(1e5)
best_ans = INF
n = 0

colors = [0 for _ in range(MAXN)]
neis: List[List[int]] = [[] for _ in range(MAXN)]


def color_ok(u: int, color: int) -> bool:
    for v in neis[u]:
        if colors[v] == 0:
            continue
        if colors[v] == color:
            return False
    return True


def dfs(u: int, cur_num: int):
    global best_ans
    if cur_num >= best_ans:
        return
    if u > n:
        best_ans = min(best_ans, cur_num)
        return
    for color in range(1, cur_num + 1):
        if color_ok(u, color):
            colors[u] = color
            dfs(u + 1, cur_num)
            colors[u] = 0
    colors[u] = cur_num + 1
    dfs(u + 1, cur_num + 1)
    colors[u] = 0


def add_bi_edge(u: int, v: int):
    neis[u].append(v)
    neis[v].append(u)


def main():
    global n
    n = int(input())
    m = int(input())
    for _ in range(m):
        u, v = read_int_list()
        add_bi_edge(u, v)
    dfs(1, 0)
    print(best_ans, end='')


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
