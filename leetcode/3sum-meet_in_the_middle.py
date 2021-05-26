# 15. 三数之和
# https://leetcode-cn.com/problems/3sum/
# meet in the middle，O(n^2)
from typing import List, Dict, Set, Tuple, Iterable
import math
import random


class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        num_pos = {x: i for i, x in enumerate(nums)}
        n = len(nums)
        ans_set = set()
        for i in range(0, n):
            for j in range(i + 1, n):
                a = nums[i]
                b = nums[j]
                if -(a + b) in num_pos:
                    ci = num_pos[-(a + b)]
                    if ci != i and ci != j:
                        t = [a, b, nums[ci]]
                        t.sort()
                        ans_set.add(tuple(t))
        return [list(t) for t in ans_set]


if __name__ == '__main__':
    nums = [-1, 0, 1, 2, -1, -4]
    nums = []
    nums = [0]
    ans = Solution().threeSum(nums)
    print(ans)
