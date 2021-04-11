# P1031 [NOIP2002 提高组] 均分纸牌
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
    n = int(input())
    arr = read_ints()
    assert len(arr) == n
    if n == 1:
        print(0)
        return
    avg = sum(arr) // n
    for i in range(n):
        arr[i] = arr[i] - avg
    cnt = 0
    for i in range(0, n - 1 + 1):
        if arr[i] != 0:
            arr[i + 1] += arr[i]
            cnt += 1
    assert arr[n - 1] == 0
    print(cnt)


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
