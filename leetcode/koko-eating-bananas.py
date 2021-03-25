# 875. 爱吃香蕉的珂珂
# https://leetcode-cn.com/problems/koko-eating-bananas/
from typing import List, Dict, Set, Tuple, Iterable
import math


class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        def time_use(k: int) -> int:
            ans = 0
            for p in piles:
                ans += int(math.ceil(p / k))
            return ans

        l = 1
        r = max(piles) + 1
        # [l, r)
        while l < r:
            m = (l + r) // 2
            t = time_use(m)
            if t <= h:
                r = m
            else:
                l = m + 1
        return l


if __name__ == '__main__':
    # piles = [3, 6, 7, 11]
    # h = 8
    # piles = [30, 11, 23, 4, 20]
    # h = 5
    piles = [30, 11, 23, 4, 20]
    h = 6
    print(Solution().minEatingSpeed(piles, h))
