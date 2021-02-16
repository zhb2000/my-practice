import math
from math import sqrt, ceil, floor, fabs, sin, cos
import sys
from typing import List, Tuple, Set, Dict, Iterable
from collections import deque

LOCAL, DEBUG = False, False


# LOCAL = True
# DEBUG = True

def read_strs() -> List[str]:
    return input().strip().split(' ')


def read_ints() -> List[int]:
    return list(map(int, read_strs()))


class Interval:
    def __init__(self, a: int = 0, b: int = 0):
        self.a = a
        self.b = b

    def __lt__(self, other):
        if self.b == other.b:
            return self.a < other.a
        else:
            return self.b < other.b

    def __repr__(self):
        return '({}, {})'.format(self.a, self.b)


MAXN = int(1e4 + 5)
intervals: List[Interval] = []
vis = [False for _ in range(MAXN)]


def clear_vis(n: int):
    for i in range(0, n):
        vis[i] = False


def check(d: int, n: int) -> bool:
    clear_vis(n)
    last = 0
    start = 0
    assert n == len(intervals)
    while start < n and last < 20000:
        if vis[start]:
            start += 1
            continue
        j = start
        while j < n:
            if not vis[j] and intervals[j].a - last <= d:
                break
            j += 1
        if j >= n:
            return False
        vis[j] = True
        inj = intervals[j]
        # assert inj.b >= last
        if last - inj.a >= d:
            last = max(last, inj.b + d)
        else:
            last += inj.b - inj.a
        if j == start:
            start += 1
    return last >= 20000


def main():
    n = int(input())
    for _ in range(n):
        a, b = read_ints()
        intervals.append(Interval(a * 2, b * 2))
    intervals.sort()
    l = 0
    r = 20000
    while l < r:
        d = (l + r) // 2
        if check(d, n):
            r = d
        else:
            l = d + 1
    if l % 2 != 0:
        print('{:.1f}'.format(l / 2.0))
    else:
        print(l // 2)


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
