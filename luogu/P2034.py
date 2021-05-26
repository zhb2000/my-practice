# P2034 选择数字
# DP、单调队列
import math
import sys
import collections
import random
import heapq
import bisect
import typing
from math import sqrt, ceil, floor, fabs, sin, cos
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


n = 0
k = 0
maxn = int(1e5 + 10)
arr = [0 for _ in range(maxn)]
f = [0 for _ in range(maxn)]
qr = 0
q = deque()


def move_right():
    global qr
    qr += 1
    ql = qr - (k + 1) + 1
    while len(q) > 0 and q[0] < ql:
        q.popleft()
    while len(q) > 0 and f[qr] < f[q[-1]]:
        q.pop()
    q.append(qr)


def q_str():
    return [f[i] for i in q]


def main():
    global n, k
    n, k = read_ints()
    for i in range(1, n + 1):
        arr[i] = int(input())
    f[1] = arr[1]
    for i in range(2, n + 1 + 1):
        move_right()
        if i <= k + 1:
            f[i] = arr[i]
        else:
            f[i] = arr[i] + f[q[0]]
        # print(f'i: {i}, q: {q_str()}')
    print(sum(arr[1:n + 1]) - min(f[n - k:n + 1 + 1]))


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
