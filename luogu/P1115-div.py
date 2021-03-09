# P1115 最大子段和
# 分治做法
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


maxn = int(2e5 + 5)
arr = [0 for _ in range(maxn)]


# [start, mid)
def mid_lmax(start: int, mid: int) -> int:
    ans = None
    cur_sum = 0
    for i in range(mid - 1, start - 1, -1):
        cur_sum += arr[i]
        if ans is None or cur_sum > ans:
            ans = cur_sum
    return ans


# [mid, stop)
def mid_rmax(mid: int, stop: int) -> int:
    ans = None
    cur_sum = 0
    for i in range(mid, stop):
        cur_sum += arr[i]
        if ans is None or cur_sum > ans:
            ans = cur_sum
    return ans


# [start, stop)
def solve(start: int, stop: int) -> int:
    if stop - start == 1:
        return arr[start]
    mid = (start + stop) // 2
    only_lmax = solve(start, mid)
    only_rmax = solve(mid, stop)
    span_max = mid_lmax(start, mid) + mid_rmax(mid, stop)
    return max(only_lmax, only_rmax, span_max)


def main():
    n = int(input())
    raw_arr = read_ints()
    for i in range(1, n + 1):
        arr[i] = raw_arr[i - 1]
    print(solve(1, n + 1))


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
