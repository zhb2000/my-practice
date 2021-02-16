# 区间子数组个数
# https://leetcode-cn.com/classic/problems/number-of-subarrays-with-bounded-maximum/description/
import math
import sys
import collections
import random
import heapq
import typing
from math import sqrt, ceil, floor, fabs, sin, cos
from typing import List, Tuple, Set, Dict, Iterable, Deque, TypeVar
from collections import deque

LOCAL, DEBUG = False, False


# LOCAL = True
# DEBUG = True


def read_strs() -> List[str]:
    return input().strip().split(' ')


def read_ints() -> List[int]:
    return list(map(int, read_strs()))


def build_string(seq: Iterable[str]) -> str:
    return ''.join(seq)


def count_in_win(win_size: int) -> int:
    return (1 + win_size) * win_size // 2


def count(arr: List[int], bound: int) -> int:
    win_size = 0
    ans = 0
    for x in arr:
        if x <= bound:
            win_size += 1
        else:
            ans += count_in_win(win_size)
            win_size = 0
    ans += count_in_win(win_size)
    return ans


class Solution:
    def numSubarrayBoundedMax(self, A: List[int], L: int, R: int) -> int:
        return count(A, R) - count(A, L - 1)


def main():
    A = [2, 1, 4, 3]
    L = 2
    R = 3
    print(Solution().numSubarrayBoundedMax(A, L, R))
    pass


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
