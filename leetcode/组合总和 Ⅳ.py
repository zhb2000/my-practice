# 组合总和 Ⅳ
# https://leetcode-cn.com/problems/combination-sum-iv/
# DP
from typing import List, Dict, Set, Tuple, Iterable, Optional
import math
import random


class Solution:
    def combinationSum4(self, nums: List[int], target: int) -> int:
        nums.sort()
        f = [0 for _ in range(target + 1)]
        for i in range(1, target + 1):
            for x in nums:
                if x > i:
                    break
                elif x == i:
                    f[i] += 1
                    break
                else:
                    f[i] += f[i - x]
        return f[target]


if __name__ == '__main__':
    sol = Solution()

    # nums = [1, 2, 3]
    # target = 4

    # nums = [9]
    # target = 3

    nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230,
            240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440,
            450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 600, 610, 620, 630, 640, 650,
            660, 670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 800, 810, 820, 830, 840, 850, 860,
            870, 880, 890, 900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 111]
    target = 999
    print(sol.combinationSum4(nums, target))
