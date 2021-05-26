# 15. 三数之和
# https://leetcode-cn.com/problems/3sum/
# 排序、双指针，O(n^2)
from typing import List, Dict, Set, Tuple, Iterable
import math
import random


class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        ans = []
        n = len(nums)
        nums.sort()

        def nxt(index: int) -> int:
            num = nums[index]
            i = index + 1
            while i < n and nums[i] == num:
                i += 1
            return i

        def pre(index: int) -> int:
            num = nums[index]
            i = index - 1
            while i > 0 and nums[i] == num:
                i -= 1
            return i

        i = 0
        while i < n:
            j = i + 1
            k = n - 1
            while j < k:
                assert j < n
                assert k > 0
                temp = nums[i] + nums[j] + nums[k]
                if temp == 0:
                    ans.append([nums[i], nums[j], nums[k]])
                    j = nxt(j)
                elif temp > 0:
                    k = pre(k)
                else:  # temp < 0
                    j = nxt(j)
            i = nxt(i)
        return ans


if __name__ == '__main__':
    nums = [-1, 0, 1, 2, -1, -4]
    # nums = []
    # nums = [0]
    ans = Solution().threeSum(nums)
    print(ans)
