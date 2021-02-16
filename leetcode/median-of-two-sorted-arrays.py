# 寻找两个正序数组的中位数
# https://leetcode-cn.com/classic/problems/median-of-two-sorted-arrays/description/
from typing import List


def a_right_ok(a: List[int], b: List[int], x: int, y: int) -> bool:
    assert 0 <= x <= len(a)
    if x == len(a):
        assert len(a) == len(b)
        return True
    if y == 0:
        return True
    if a[x] >= b[y - 1]:
        return True
    return False


def b_right_ok(a: List[int], b: List[int], x: int, y: int) -> bool:
    assert 0 <= y <= len(b)
    if y == len(b):
        return True
    if x == 0:
        return True
    if b[y] >= a[x - 1]:
        return True
    return False


def avg2(x: int, y: int) -> float:
    return (x + y) / 2


def solve(a: List[int], b: List[int]) -> float:
    assert len(a) >= len(b)
    len_sum = len(a) + len(b)
    if len(b) == 0:
        if len_sum % 2 != 0:
            return a[len(a) // 2]
        else:
            return avg2(a[(len(a) - 1) // 2], a[(len(a) - 1) // 2 + 1])
    l = len_sum // 2
    lbound = 0
    rbound = l + 1
    while True:
        x = (lbound + rbound) // 2
        y = l - x
        if y > len(b) or not a_right_ok(a, b, x, y):  # x must be bigger
            if y <= len(b):
                assert b_right_ok(a, b, x, y)
            lbound = x + 1
        elif not b_right_ok(a, b, x, y):  # x must be smaller
            assert a_right_ok(a, b, x, y)
            rbound = x
        else:  # find the x
            numl = 0
            if x == 0:
                numl = b[y - 1]
            elif y == 0:
                numl = a[x - 1]
            else:
                numl = max(a[x - 1], b[y - 1])
            numr = 0
            if x == len(a):
                numr = b[y]
            elif y == len(b):
                numr = a[x]
            else:
                numr = min(a[x], b[y])
            if len_sum % 2 != 0:
                return numr
            else:
                return avg2(numl, numr)


class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        if len(nums1) < len(nums2):
            nums1, nums2 = nums2, nums1
        return solve(nums1, nums2)


if __name__ == '__main__':
    pass
