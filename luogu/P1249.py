# P1249 最大乘积
# 数学，贪心
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


def solve(n: int):
    if n == 3:
        return [1, 2]
    if n == 4:
        return [1, 3]
    sum_ = 0
    arr = []
    for num in range(2, n):
        sum_ += num
        arr.append(num)
        if sum_ >= n:
            break
    if sum_ > n:
        g = sum_ - n
        if g == 1:
            arr[0] = None
            arr[-1] += 1
        else:
            arr[g - 2] = None
    return arr


def main():
    n = int(input())
    arr = solve(n)
    result = 1
    isfirst = True
    for num in arr:
        if num is None:
            continue
        if isfirst:
            isfirst = False
        else:
            print(' ', end='')
        print(num, end='')
        result *= num
    print()
    print(result)


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
