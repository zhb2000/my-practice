# 小张刷题计划
# https://leetcode-cn.com/classic/problems/xiao-zhang-shua-ti-ji-hua/description/
# 最大值最小化、二分答案、贪心
# 判断答案是否成立时需要贪心
from typing import List, Dict, Set, Tuple, Iterable, Optional
import math
import random


class Solution:
    def __init__(self):
        self.time = []
        self.m = 0

    def minTime(self, time: List[int], m: int) -> int:
        self.time = time
        self.m = m
        l = 0
        r = sum(time) + 1
        while l < r:
            mid = (l + r) // 2
            if self.available(mid):
                r = mid
            else:
                l = mid + 1
        return l

    def available(self, t: int) -> bool:
        n = len(self.time)
        day_cnt = 0
        i = 0
        dsum = 0
        dmax = -1
        while i < n:
            dmax = max(dmax, self.time[i])
            dsum += self.time[i]
            if dsum - dmax > t:
                day_cnt += 1
                dsum = 0
                dmax = -1
            else:
                i += 1
        assert dmax != -1
        day_cnt += 1
        return day_cnt <= self.m


if __name__ == '__main__':
    time = [1, 2, 3, 3]
    m = 2
    print(Solution().minTime(time, m))
    time = [999, 999, 999]
    m = 4
    print(Solution().minTime(time, m))
