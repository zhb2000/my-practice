# 18. 四数之和
# https://leetcode-cn.com/problems/4sum/
# meet-in-the-middle
from typing import List, Dict, Set, Tuple, Iterable, Optional
import math
import random


class Solution:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        n = len(nums)
        sum_poses = {}
        for i in range(0, n):
            for j in range(i+1,n):
                s = nums[i]+nums[j]
                if s not in sum_poses:
                    sum_poses[s] = set()
                sum_poses[s].add((i, j))
        ans = set()
        for i in range(0, n):
            for j in range(i+1, n):
                a = nums[i]
                b = nums[j]
                if target - (a+b) in sum_poses:
                    for k, l in sum_poses[target-(a+b)]:
                        if k != i and k != j and l != i and l != j:
                            c = nums[k]
                            d = nums[l]
                            temp = [a,b,c,d]
                            temp.sort()
                            ans.add(tuple(temp))
        return [list(t) for t in ans]



if __name__ == '__main__':
    # nums = [1, 0, -1, 0, -2, 2]
    # target = 0
    nums = []
    target = 0
    print(Solution().fourSum(nums, target))
