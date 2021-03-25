# P1018 [NOIP2000 提高组] 乘积最大
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


def main():
    n, k = read_ints()
    seq = input().strip()

    def number(l: int, r: int) -> int:
        return int(seq[l:r + 1])

    f = [[0 for j in range(k + 1)] for i in range(n)]
    for i in range(0, n):
        f[i][0] = number(0, i)
        max_op_num = min(i, k)
        for j in range(1, max_op_num + 1):
            for x in range(0, i):
                temp = f[x][j - 1] * number(x + 1, i)
                f[i][j] = max(f[i][j], temp)
    print(f[n - 1][k])


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
