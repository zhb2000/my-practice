# 区间和的个数
# https://leetcode-cn.com/classic/problems/count-of-range-sum/description/
# O(nlogn) 做法，分治、归并排序、前缀和
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


def avg2(a: int, b: int) -> int:
    return (a + b) // 2


class Solution:
    # [start, stop)
    def get_cans(self, start: int, stop: int, pre: List[int], upper: int, lower: int) -> int:
        mid = avg2(start, stop)
        ans = 0
        l = mid
        r = mid
        # [l, r)
        for i in range(start, mid):
            while l < stop and pre[l] < pre[i] + lower:
                l += 1
            while r < stop and pre[r] <= pre[i] + upper:
                r += 1
            ans += r - l
        return ans

    def merge(self, start: int, stop: int, pre: List[int]):
        temp_arr = []
        mid = avg2(start, stop)
        i = start
        j = mid
        while i < mid and j < stop:
            if pre[i] < pre[j]:
                temp_arr.append(pre[i])
                i += 1
            else:
                temp_arr.append(pre[j])
                j += 1
        if i < mid:
            while i < mid:
                temp_arr.append(pre[i])
                i += 1
        elif j < stop:
            while j < stop:
                temp_arr.append(pre[j])
                j += 1
        for offset in range(len(temp_arr)):
            pre[start + offset] = temp_arr[offset]

    # [start, stop)
    def solve(self, start: int, stop: int, pre: List[int], lower: int, upper: int) -> int:
        if stop - start == 1:
            return 0
        mid = avg2(start, stop)
        lans = self.solve(start, mid, pre, lower, upper)
        rans = self.solve(mid, stop, pre, lower, upper)
        cans = self.get_cans(start, stop, pre, upper, lower)
        self.merge(start, stop, pre)
        return lans + rans + cans

    def countRangeSum(self, nums: List[int], lower: int, upper: int) -> int:
        pre = [0 for _ in range(len(nums) + 1)]
        for i in range(1, len(nums) + 1):
            j = i - 1
            pre[i] = pre[i - 1] + nums[j]
        return self.solve(0, len(pre), pre, lower, upper)


def main():
    nums = [-2, 5, -1]
    lower = -2
    upper = 2
    print(Solution().countRangeSum(nums, lower, upper))


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
