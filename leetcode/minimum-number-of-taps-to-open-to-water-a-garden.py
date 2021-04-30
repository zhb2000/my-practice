# 灌溉花园的最少水龙头数目
# https://leetcode-cn.com/classic/problems/minimum-number-of-taps-to-open-to-water-a-garden/description/
# 贪心、最少线段覆盖
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


class Segment:
    def __init__(self, l: int, r: int):
        self.l = l
        self.r = r

    def __lt__(self, other):
        if self.l == other.l:
            slen = self.r - self.l + 1
            olen = other.r - other.l + 1
            return slen > olen
        return self.l < other.l

    def __repr__(self):
        return f'({self.l}, {self.r})'


class Solution:
    def minTaps(self, n: int, ranges: List[int]) -> int:
        x = [Segment(max(i - r, 0), min(i + r, n)) for i, r in enumerate(ranges) if r > 0]
        x.sort()
        sz = len(x)
        if sz == 0:
            return -1
        if x[0].l > 0:
            return -1
        fix = 0
        ans = 1
        change = -1
        for i in range(1, sz):
            if x[i].l <= x[fix].r:
                if x[i].r > x[fix].r:
                    if change == -1:
                        change = i
                        ans += 1
                    elif x[i].r > x[change].r:
                        change = i
                if i + 1 < sz and x[i + 1].l > x[fix].r:
                    if change != -1:
                        fix = change
                        change = -1
            else:
                return -1
        return ans


def main():
    # n = 5
    # ranges = [3, 4, 1, 1, 0, 0]
    # n = 3
    # ranges = [0, 0, 0, 0]
    # n = 7
    # ranges = [1, 2, 1, 0, 2, 1, 0, 1]
    # n = 8
    # ranges = [4, 0, 0, 0, 0, 0, 0, 0, 4]
    n = 8
    ranges = [4, 0, 0, 0, 4, 0, 0, 0, 4]
    print(Solution().minTaps(n, ranges))


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
