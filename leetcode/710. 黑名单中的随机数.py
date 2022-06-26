# 710. 黑名单中的随机数
# https://leetcode.cn/problems/random-pick-with-blacklist/
from typing import List, Dict, Set, Tuple, Iterable, Optional
import math
import random


class Solution:
    def __init__(self, n: int, blacklist: List[int]):
        self.white_range = n - len(blacklist)
        blackset = set(blacklist)
        # black_in_range = filter(lambda x: x in blackset, range(0, self.white_range))
        black_in_range = filter(lambda x: x < self.white_range, blacklist)
        white_not_in_range = filter(lambda x: x not in blackset, range(self.white_range, n))
        self.map = dict(zip(black_in_range, white_not_in_range))

    def pick(self) -> int:
        x = random.randint(0, self.white_range - 1)
        return self.map.get(x, x)


if __name__ == '__main__':
    pass
