# SP1805 HISTOGRA - Largest Rectangle in a Histogram
# vjudge：https://vjudge.net/problem/SPOJ-HISTOGRA
# 悬线法
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


MAXN = int(1e5) + 5
left_most = [0 for _ in range(MAXN)]
right_most = [0 for _ in range(MAXN)]


def solve(h: List[int]) -> int:
    n = len(h) - 1
    for i in range(1, n + 1):
        l = i
        while l >= 1 and h[l] >= h[i]:
            left_most[i] = l
            if left_most[l] != l:
                assert left_most[l] < l
                left_most[i] = left_most[l]
                l = left_most[l] - 1
            else:
                l -= 1
    for i in range(n, 1 - 1, -1):
        r = i
        while r <= n and h[r] >= h[i]:
            right_most[i] = r
            if right_most[r] != r:
                assert right_most[r] > r
                right_most[i] = right_most[r]
                r = right_most[r] + 1
            else:
                r += 1
    ans = 0
    for i in range(1, n + 1):
        temp_ans = (right_most[i] - left_most[i] + 1) * h[i]
        ans = max(ans, temp_ans)
    return ans


def main():
    while True:
        h = read_ints()
        if h[0] == 0:
            break
        print(solve(h))


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
