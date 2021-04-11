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


def round_rad(x: float) -> float:
    if x > 1.0:
        return 1.0
    elif x < -1.0:
        return -1.0
    return x


def route(a: float, b: float, r: float, theta: float, dist_ab: float) -> float:
    # if a * a + dist_ab * dist_ab <= b * b:
    #     return dist_ab
    # if b * b + dist_ab * dist_ab <= a * a:
    #     return dist_ab
    ana = math.acos(round_rad(r / a))
    anb = math.acos(round_rad(r / b))
    if ana + anb >= theta:
        return dist_ab
    anm = theta - (ana + anb)
    x = sqrt(abs(a ** 2 - r ** 2))
    y = sqrt(abs(b ** 2 - r ** 2))
    return x + r * anm + y


def dot(v, w):
    ans = 0.0
    for x, y in zip(v, w):
        ans += x * y
    return ans


def minus(v, w):
    return [x - y for x, y in zip(v, w)]


def main():
    n, m = read_ints()
    r = float(input())
    o = read_ints()
    # assert len(o) == n
    points = [read_ints() for _ in range(m)]
    for i in range(m):
        route_sum = 0.0
        for j in range(m):
            if i == j:
                continue
            a = math.dist(points[i], o)
            b = math.dist(points[j], o)
            dist_ab = math.dist(points[i], points[j])
            v = minus(points[i], o)
            w = minus(points[j], o)
            cos_theta = dot(v, w) / (a * b)
            theta = math.acos(round_rad(cos_theta))
            rlen = route(a, b, r, theta, dist_ab)
            route_sum += rlen
        print(f'{route_sum:.14f}')


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
