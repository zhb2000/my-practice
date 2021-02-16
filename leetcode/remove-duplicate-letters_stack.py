# 去除重复字母
# 单调栈
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


def build_string(seq: Iterable[str]) -> str:
    return ''.join(seq)


class Solution:
    def removeDuplicateLetters(self, s: str) -> str:
        st = []
        st_letters: Set[str] = set()
        last_pos = {ch: i for i, ch in enumerate(s)}
        for i, ch in enumerate(s):
            if ch not in st_letters:
                while len(st) != 0 and st[-1] > ch and i < last_pos[st[-1]]:
                    st_letters.discard(st[-1])
                    st.pop()
                st.append(ch)
                st_letters.add(ch)
        return build_string(st)


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
