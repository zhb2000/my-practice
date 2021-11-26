# P1080 [NOIP2012 提高组] 国王游戏
# 贪心、数学
import math
import sys
import collections
import random
import heapq
import bisect
import typing
from math import sqrt, ceil, floor, fabs, sin, cos, gcd
from typing import List, Tuple, Set, Dict, Iterable, Deque, TypeVar, Optional
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


class Person:
    def __init__(self, a: int, b: int):
        self.a = a
        self.b = b
        self.value = a * b

    def __lt__(self, other):
        return self.value < other.value


def main():
    n = int(input())
    king_a, _ = read_ints()
    people = []
    for _ in range(n):
        a, b = read_ints()
        people.append(Person(a,b))
    people.sort()
    ans = 0
    tot = king_a
    for x in people:
        ans = max(ans, tot // x.b)
        tot *= x.a
    print(ans)


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
