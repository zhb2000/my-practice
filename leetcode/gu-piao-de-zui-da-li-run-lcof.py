# 剑指 Offer 63. 股票的最大利润
# https://leetcode-cn.com/classic/problems/gu-piao-de-zui-da-li-run-lcof/description
import math
import sys
import collections
import random
import heapq
from math import sqrt, ceil, floor, fabs, sin, cos
from typing import List, Tuple, Set, Dict, Iterable
from collections import deque

LOCAL, DEBUG = False, False


# LOCAL = True
# DEBUG = True

def read_strs() -> List[str]:
    return input().strip().split(' ')


def read_ints() -> List[int]:
    return list(map(int, read_strs()))


def get_max(prices: List[int], start: int, stop: int) -> int:
    assert stop - start >= 1
    if stop - start == 1:
        return prices[start]
    else:
        mid = (start + stop) // 2
        lmax = get_max(prices, start, mid)
        rmax = get_max(prices, mid, stop)
        return max(lmax, rmax)


def get_min(prices: List[int], start: int, stop: int) -> int:
    assert stop - start >= 1
    if stop - start == 1:
        return prices[start]
    else:
        mid = (start + stop) // 2
        lmin = get_min(prices, start, mid)
        rmin = get_min(prices, mid, stop)
        return min(lmin, rmin)


def get_ans(prices: List[int], start: int, stop: int) -> int:
    assert stop - start >= 1
    if stop - start == 1:
        return 0
    else:
        mid = (start + stop) // 2
        lmin = get_min(prices, start, mid)
        rmax = get_max(prices, mid, stop)
        the_ans = rmax - lmin
        lans = get_ans(prices, start, mid)
        rans = get_ans(prices, mid, stop)
        return max(the_ans, lans, rans)


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        if n == 0:
            return 0
        else:
            return max(0, get_ans(prices, 0, n))


def main():
    prices = [7,6,4,3,1]
    print(Solution().maxProfit(prices))
    pass


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
