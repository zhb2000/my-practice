# P1896 [SCOI2005]互不侵犯
# 状压 DP
import math
import sys
import collections
import random
import heapq
import bisect
import typing
from math import sqrt, ceil, floor, fabs, sin, cos
from typing import List, Tuple, Set, Dict, Iterable, Deque, TypeVar, Optional
from collections import deque
from bisect import bisect_left, bisect_right

LOCAL, DEBUG = False, False


# LOCAL = True
# DEBUG = True


def read_strs() -> List[str]:
    return input().split()


def read_ints() -> List[int]:
    return list(map(int, read_strs()))


def build_string(seq: Iterable[str]) -> str:
    return ''.join(seq)


MAXN = 9 + 1
MAXK = MAXN ** 2
MAXCNT = 2 ** MAXN
f = [[[0 for l in range(MAXK)] for j in range(MAXCNT)] for i in range(MAXN)]
sta = [0 for _ in range(MAXCNT)]
sit = [0 for _ in range(MAXCNT)]
cnt = 0
n = 0
K = 0


def dfs(cur: int, bitvec: int, has_put_num: int):
    global n, cnt
    if cur >= n:
        sit[cnt] = bitvec
        sta[cnt] = has_put_num
        cnt += 1
        return
    dfs(cur + 1, bitvec, has_put_num)
    dfs(cur + 2, bitvec | (1 << cur), has_put_num + 1)


def compatible(j: int, x: int) -> bool:
    return (sit[j] & sit[x] == 0
            and (sit[j] << 1) & sit[x] == 0
            and sit[j] & (sit[x] << 1) == 0)


def main():
    global n, K, cnt
    n, K = read_ints()
    dfs(0, 0, 0)
    for j in range(cnt):
        f[0][j][sta[j]] = 1
    for i in range(1, n):
        for j in range(cnt):
            for x in range(cnt):
                if not compatible(j, x):
                    continue
                for l in range(sta[j], K + 1):
                    f[i][j][l] += f[i - 1][x][l - sta[j]]
    ans = 0
    for j in range(cnt):
        ans += f[n - 1][j][K]
    print(ans)


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        # out_file = open('out.txt', 'w')
        sys.stdin = in_file
        # sys.stdout = out_file
    main()
