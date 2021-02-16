# 零钱兑换
# https://leetcode-cn.com/classic/problems/coin-change/description/
import math
import sys
import collections
import random
import heapq
from math import sqrt, ceil, floor, fabs, sin, cos
from typing import List, Tuple, Set, Dict, Iterable
from collections import deque

LOCAL, DEBUG = False, False


# LOCAL = True
# DEBUG = True

def read_strs() -> List[str]:
    return input().strip().split(' ')


def read_ints() -> List[int]:
    return list(map(int, read_strs()))


class Solution:
    def __init__(self):
        MAX_AMT = int(1e4) + 5
        self.dp_arr = [-100 for _ in range(MAX_AMT)]
        self.coins: List[int] = []

    def coinChange(self, coins: List[int], amount: int) -> int:
        self.coins = coins
        return self.dp(amount)

    def dp(self, amount: int) -> int:
        if amount < 0:
            return -1
        elif amount == 0:
            return 0
        elif self.dp_arr[amount] != -100:
            return self.dp_arr[amount]
        else:
            min_num = None
            for coin in self.coins:
                temp = self.dp(amount - coin)
                if temp != -1:
                    if min_num is None:
                        min_num = temp
                    else:
                        min_num = min(min_num, temp)
            if min_num is None:
                self.dp_arr[amount] = -1
            else:
                self.dp_arr[amount] = min_num + 1
            return self.dp_arr[amount]


def main():
    coins = [100, 76, 1]
    amount = 404
    print(Solution().coinChange(coins, amount))
    pass


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
