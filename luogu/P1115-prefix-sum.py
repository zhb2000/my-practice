# P1115 最大子段和
# 前缀和做法
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


maxn = int(2e5 + 5)
arr = [0 for _ in range(maxn)]
pre_sum = [0 for _ in range(maxn)]


def main():
    n = int(input())
    raw_arr = read_ints()
    for i in range(1, n + 1):
        arr[i] = raw_arr[i - 1]
    for i in range(1, n + 1):
        pre_sum[i] = pre_sum[i - 1] + arr[i]
    cur_min_pre_sum = 0
    ans = None
    for i in range(1, n+1):
        temp_ans = pre_sum[i]-cur_min_pre_sum
        if ans is None or temp_ans > ans:
            ans = temp_ans
        cur_min_pre_sum = min(cur_min_pre_sum, pre_sum[i])
    print(ans)


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
