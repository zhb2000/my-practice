# P1040 [NOIP2003 提高组] 加分二叉树
# 区间 DP
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


MAXN = 30 + 3
f_arr = [[-1 for j in range(MAXN)] for i in range(MAXN)]
root_of = [[-1 for j in range(MAXN)] for i in range(MAXN)]
goal = [0 for _ in range(MAXN)]
lch = [0 for _ in range(MAXN)]
rch = [0 for _ in range(MAXN)]
pre_seq = []


def f(i: int, j: int) -> int:
    if j < i:  # empty tree
        return 1
    if i == j:  # leaf
        return goal[i]
    if f_arr[i][j] != -1:
        return f_arr[i][j]
    for k in range(i, j + 1):
        temp = f(i, k - 1) * f(k + 1, j) + goal[k]
        if temp > f_arr[i][j]:
            f_arr[i][j] = temp
            root_of[i][j] = k
    # assert f_arr[i][j] != -1
    # assert root_of[i][j] != -1
    return f_arr[i][j]


def traverse_tree(i: int, j: int):
    if i == j:
        pre_seq.append(i)
        return
    root = root_of[i][j]
    # print(f'i: {i}, j: {j}, root: {root}')
    # assert root != -1
    # assert i <= root <= j
    pre_seq.append(root)
    if i == j:
        return
    if i <= root - 1:
        traverse_tree(i, root - 1)
    if root + 1 <= j:
        traverse_tree(root + 1, j)
    return root


def main():
    n = int(input())
    arr = read_ints()
    for i, g in enumerate(arr):
        goal[i + 1] = g
    print(f(1, n))
    traverse_tree(1, n)
    for i, x in enumerate(pre_seq):
        if i != 0:
            print(' ', end='')
        print(x, end='')


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
