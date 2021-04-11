# P1007 独木桥
# 思维题
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
    pos = [0]
    length = int(input())
    n = int(input())
    if n == 0:
        print('0 0')
        return
    pos.extend(read_ints())
    assert len(pos) == n + 1
    min_ans = 0
    max_ans = 0
    for i in range(1, n + 1):
        p = pos[i]
        min_sp = min(p - 0, length + 1 - p)
        max_sp = max(p - 0, length + 1 - p)
        min_ans = max(min_ans, min_sp)
        max_ans = max(max_ans, max_sp)
    print(f'{min_ans} {max_ans}')


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
