import math
import sys
import collections
import random
import heapq
import bisect
import typing
from math import sqrt, ceil, floor, fabs, sin, cos
from typing import List, Tuple, Set, Dict, Iterable, Deque, TypeVar
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


MAXN = int(1e3) + 3
MOD = int(1e9) + 7
n = 0
obs: List[int] = []
f: List[Dict[int, int]] = [{} for _ in range(MAXN)]
fsum = [0 for _ in range(MAXN)]
is_obs = [False for _ in range(MAXN)]


# return -1 if invalid
def get(u: int, step: int) -> int:
    tree_num = 0
    # for(int cur=u-step; cur>=obs[0]; cur-=step)
    for cur in range(u - step, obs[0] - 1, -step):
        if is_obs[cur]:
            if cur == obs[0]:  # special
                if tree_num > 0:
                    return 1
                else:
                    return -1  # invalid
            if step in f[cur]:  # both connect and not connect is ok
                return fsum[cur]
            else:  # can't connect and can't plant more
                if tree_num > 0:
                    return fsum[cur]
                else:
                    return -1  # invalid
        else:
            tree_num += 1
    return -1  # invalid, not meet any obstacle


def main():
    global n, obs
    n = int(input())
    obs = read_ints()
    assert len(obs) == n
    for u in obs:
        is_obs[u] = True
    for u in obs[1:]:
        for step in range(1, u - obs[0] + 1):
            ret = get(u, step)
            if ret != -1:
                f[u][step] = ret
        fsum[u] = 0
        for val in f[u].values():
            fsum[u] = (fsum[u] + val) % MOD
    print(fsum[obs[n - 1]])


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
