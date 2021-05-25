# 最接近的三数之和
# https://leetcode-cn.com/classic/problems/3sum-closest/description/
# 排序、双指针
from typing import List, Dict, Set, Tuple, Iterable, Optional
import math
import random


class Solution:
    def threeSumClosest(self, nums: List[int], target: int) -> int:
        ans = None

        def update_ans(a: int, b: int, c: int, ans) -> int:
            if ans is None or abs((a + b + c) - target) < abs(ans - target):
                return a + b + c
            return ans

        nums.sort()
        n = len(nums)
        for i in range(0, n):
            j = i + 1
            k = n - 1
            while j < k:
                assert j < n
                assert k >= 0
                temp = nums[i] + nums[j] + nums[k]
                if temp == target:
                    return target
                elif temp < target:
                    ans = update_ans(nums[i], nums[j], nums[k], ans)
                    j += 1
                else:  # temp > target
                    ans = update_ans(nums[i], nums[j], nums[k], ans)
                    k -= 1
        assert ans is not None
        return ans


if __name__ == '__main__':
    nums = [-1, 2, 1, -4]
    target = 1
    print(Solution().threeSumClosest(nums, target))
