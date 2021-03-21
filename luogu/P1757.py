# P1757 通天之分组背包
# 分组背包
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


MAXW = 1000 + 5
MAXN = 1000 + 5
w = [0 for _ in range(MAXN)]
v = [0 for _ in range(MAXN)]
f = [0 for _ in range(MAXW)]
group = {}


def main():
    W, n = read_ints()
    for i in range(1, n + 1):
        a, b, c = read_ints()
        w[i] = a
        v[i] = b
        if c not in group:
            group[c] = []
        group[c].append(i)
    for k in group:
        for j in range(W, 0 - 1, -1):
            for i in group[k]:
                if j - w[i] >= 0:
                    f[j] = max(f[j], f[j - w[i]] + v[i])
    print(f[W])


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
