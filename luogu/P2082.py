# P2082 区间覆盖(加强版)
# 排序、贪心
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


class Interval:
    def __init__(self, l: int, r: int):
        self.l = l
        self.r = r

    def __lt__(self, other):
        if self.l == other.l:
            tlen = self.r - self.l + 1
            olen = other.r - other.l + 1
            return tlen > olen
        return self.l < other.l


def main():
    n = int(input())
    intervals = []
    for _ in range(n):
        l, r = read_ints()
        intervals.append(Interval(l, r))
    intervals.sort()
    if len(intervals) == 0:
        print(0)
        return
    ans = 0
    conti_l = intervals[0].l
    conti_r = intervals[0].r
    for x in intervals[1:]:
        if x.l <= conti_r + 1:
            conti_r = max(conti_r, x.r)
        else:
            ans += conti_r - conti_l + 1
            conti_l = x.l
            conti_r = x.r
    ans += conti_r - conti_l + 1
    print(ans)


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
