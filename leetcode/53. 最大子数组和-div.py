# 最大子序和（分治）
# https://leetcode-cn.com/classic/problems/maximum-subarray/description/
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


def max_sum(nums: List[int], start: int, stop: int) -> int:
    assert stop - start >= 0
    if stop - start == 1:
        return nums[start]
    else:
        mid = (start + stop) // 2
        result = max(max_sum(nums, start, mid), max_sum(nums, mid, stop))
        v = 0
        max_l_mid = nums[mid - 1]
        for i in range(mid - 1, start - 1, -1):
            v += nums[i]
            max_l_mid = max(max_l_mid, v)
        v = 0
        max_r_mid = nums[mid]
        for i in range(mid, stop):
            v += nums[i]
            max_r_mid = max(max_r_mid, v)
        return max(result, max_l_mid + max_r_mid)


class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        return max_sum(nums, 0, len(nums))


def main():
    arr = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
    print(Solution().maxSubArray(arr))
    pass


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
