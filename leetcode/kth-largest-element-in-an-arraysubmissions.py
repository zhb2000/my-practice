# 215. 数组中的第K个最大元素
# https://leetcode-cn.com/problems/kth-largest-element-in-an-array
# Top K 问题、分治、快排
from typing import List, Dict, Set, Tuple, Iterable
import math
import random


class Solution:
    # return pivot pos
    # [l, pos-1] less than pivot, [pos, r] geq pivot, arr[pos]=pivot
    def split(self, arr: List[int], l: int, r: int) -> int:
        assert l <= r
        if r - l + 1 == 1:
            return l
        v = arr[r]
        i = l
        j = r - 1
        while i < j:
            while i < j:
                if arr[i] < v:
                    i += 1
                else:
                    arr[i], arr[j] = arr[j], arr[i]
                    break
            while i < j:
                if arr[j] >= v:
                    j -= 1
                else:
                    arr[i], arr[j] = arr[j], arr[i]
                    break
        pos = i if arr[i] >= v else i + 1
        assert l <= pos <= r
        arr[pos], arr[r] = arr[r], arr[pos]
        return pos

    def top_k_pos(self, arr: List[int], l: int, r: int, k: int) -> int:
        # if r - l + 1 == 1:
        #     return l
        p = self.split(arr, l, r)
        geq_num = r - p + 1
        if geq_num == k:
            return p
        elif geq_num > k:
            return self.top_k_pos(arr, p + 1, r, k)
        else:
            return self.top_k_pos(arr, l, p - 1, k - geq_num)

    def findKthLargest(self, nums: List[int], k: int) -> int:
        random.shuffle(nums)
        p = self.top_k_pos(nums, 0, len(nums) - 1, k)
        return nums[p]


if __name__ == '__main__':
    # nums = [3, 2, 1, 5, 6, 4]
    # k = 2
    nums = [3, 2, 3, 1, 2, 4, 5, 5, 6]
    k = 4
    # nums = [3]
    # k = 1
    # nums = [3, 2]
    # k = 2
    # nums = [3, 2]
    # k = 1
    ans = Solution().findKthLargest(nums, k)
    print(ans)
    print(nums)
    # sol = Solution()
    # print(sol.split(nums, 0, len(nums) - 1))
    # print(nums)
