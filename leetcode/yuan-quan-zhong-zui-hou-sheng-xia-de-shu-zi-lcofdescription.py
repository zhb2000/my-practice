# 剑指 Offer 62. 圆圈中最后剩下的数字
# https://leetcode-cn.com/classic/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/description/
# 约瑟夫环问题、DP
from typing import List, Dict, Set, Tuple, Iterable
import math
import random


class Solution:
    def lastRemaining(self, n: int, m: int) -> int:
        # f(1) = 0
        # f(n) = (m+f(n-1)) % n
        f = 0
        for i in range(2, n + 1):
            f = (m + f) % i
            # print(f'f({i})={f}')
        return f


if __name__ == '__main__':
    n = 10
    m = 17
    print(Solution().lastRemaining(n, m))
