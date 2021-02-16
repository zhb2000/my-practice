# 去除重复字母
# https://leetcode-cn.com/classic/problems/remove-duplicate-letters/description/
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


def a2i(ch: str) -> int:
    return ord(ch) - ord('a')


def i2a(i: int) -> str:
    return chr(i + ord('a'))


def build_string(lst: Iterable[str]) -> str:
    return ''.join(lst)


class Solution:
    def __init__(self):
        MAXN = int(1e4 + 5)
        # letters at the right of i
        self.right_letters: List[Set[str]] = [set() for _ in range(MAXN)]
        # letters in ans
        self.ans_letters: Set[str] = set()
        # num of different letters in s
        self.type_cnt = 0

    def calc_right_letters(self, s: str):
        slen = len(s)
        # from slen-1 to 0
        for i in range(slen - 1, -1, -1):
            ch = s[i]
            if i < slen - 1:  # not the last
                self.right_letters[i] = self.right_letters[i + 1].copy()
            self.right_letters[i].add(ch)

    def right_available(self, j: int, still_need: int) -> bool:
        right_types = 0
        for ch in self.right_letters[j]:
            if ch not in self.ans_letters:
                right_types += 1
        return right_types >= still_need

    def solve(self, s: str) -> str:
        slen = len(s)
        ans = ['' for _ in range(self.type_cnt)]
        nxtp = 0
        for i in range(0, self.type_cnt):
            assert nxtp < slen
            stil_need = self.type_cnt - i
            # select minimum available letter
            min_a = 100
            select_pos = 0
            for j in range(nxtp, slen):
                ch = s[j]
                if a2i(ch) < min_a \
                        and ch not in self.ans_letters \
                        and self.right_available(j, stil_need):
                    min_a = a2i(ch)
                    select_pos = j
            assert min_a < 100
            select_letter = i2a(min_a)
            ans[i] = select_letter
            self.ans_letters.add(select_letter)
            nxtp = select_pos + 1
        return build_string(ans)

    def removeDuplicateLetters(self, s: str) -> str:
        self.type_cnt = len(set(s))
        self.calc_right_letters(s)
        return self.solve(s)


def main():
    s = "leetcode"
    print(Solution().removeDuplicateLetters(s))


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
