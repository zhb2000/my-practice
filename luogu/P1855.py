# P1855 榨取kkksc03
# 二维费用背包
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


MAXM = 200 + 5
MAXT = 200 + 5
MAXN = 100 + 5
m = [0 for _ in range(MAXN)]
t = [0 for _ in range(MAXN)]
f = [[0 for j in range(MAXT)] for i in range(MAXM)]


def main():
    n, M, T = read_ints()
    for i in range(1, n + 1):
        money, time = read_ints()
        m[i] = money
        t[i] = time
    for i in range(1, n + 1):
        for j in range(M, m[i] - 1, -1):
            for k in range(T, t[i] - 1, -1):
                f[j][k] = max(f[j][k], f[j - m[i]][k - t[i]] + 1)
    print(f[M][T])


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
