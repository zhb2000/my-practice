# P1048 [NOIP2005 普及组] 采药
# 0-1 背包
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


MAXN = 100 + 5
MAXW = 1000 + 5
f = [0 for _ in range(MAXW)]
w = [0 for _ in range(MAXN)]
v = [0 for _ in range(MAXN)]


def main():
    W, n = read_ints()
    for i in range(1, n + 1):
        weight, value = read_ints()
        w[i] = weight
        v[i] = value
    for i in range(1, n + 1):
        for j in range(W, w[i] - 1, -1):
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
