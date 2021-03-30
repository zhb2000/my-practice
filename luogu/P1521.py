# P1521 求逆序对
# 线性 DP
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


MAXN = 100 + 3
MOD = 10000
f_arr = [[-1 for j in range(MAXN * MAXN)] for i in range(MAXN)]


def f(i: int, j: int) -> int:
    if f_arr[i][j] != -1:
        return f_arr[i][j]
    if j == 0:
        return 1
    ans = 0
    n1max = (i - 1) * (i - 1 - 1) // 2
    for x in range(0, i - 1 + 1):
        if j - x > n1max:
            continue
        if j - x < 0:
            break
        ans = (ans + f(i - 1, j - x)) % MOD
    f_arr[i][j] = ans
    return ans


def main():
    n, k = read_ints()
    print(f(n, k))


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
