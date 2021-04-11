# P3743 kotori的设备
# 二分答案
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


MAXN = 100000 + 5
a = [0 for _ in range(MAXN)]
b = [0 for _ in range(MAXN)]
n = 0
p = 0


def can_last(t: float) -> bool:
    # print(f'can_last({t})')
    need_sum = 0.0
    for i in range(1, n + 1):
        if b[i] >= a[i] * t:
            continue
        need_sum += a[i] * t - b[i]
    return p * t >= need_sum


def can_always() -> bool:
    return sum(a[1:n + 1]) <= p


def solve() -> float:
    if can_always():
        return -1.0
    l = 0.0
    r = 1e10
    eps = 1e-5
    while r - l > eps:
        m = (l + r) / 2
        if can_last(m):
            l = m + eps
        else:
            r = m
    return l


def main():
    global n, p
    n, p = read_ints()
    for i in range(1, n + 1):
        av, bv = read_ints()
        a[i] = av
        b[i] = bv
    print(f'{solve():.10f}')


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
