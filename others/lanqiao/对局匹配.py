import math
import sys
from typing import List, Tuple, Set, Dict, Iterable
from math import sqrt, ceil, floor, fabs, sin, cos

LOCAL, DEBUG = False, False


# LOCAL = True
# DEBUG = True

def read_strs() -> List[str]:
    return input().split(' ')


def read_ints() -> List[int]:
    return list(map(int, read_strs()))


MAXNUM = 100000 + 5
arr: List[int] = []
cnt = [0 for _ in range(MAXNUM)]
dp = [0 for _ in range(MAXNUM)]


def get_group(start: int, k: int, maxnum: int) -> int:
    i = 0
    while start + k * i <= maxnum:
        num = start + k * i
        if i == 0:
            dp[i] = cnt[num]
        elif i - 1 == 0:
            dp[i] = max(cnt[num], dp[i - 1])
        else:
            dp[i] = max(cnt[num] + dp[i - 2], dp[i - 1])
        i += 1
    return dp[i - 1]


def solve(k: int, maxnum: int) -> int:
    if k == 0:
        s = set()
        for num in arr:
            s.add(num)
        return len(s)
    else:
        ans = 0
        for start in range(0, k):
            if start <= maxnum:
                ans += get_group(start, k, maxnum)
            else:
                break
        return ans


def main():
    global arr
    n, k = read_ints()
    arr = read_ints()
    maxnum = -1
    for num in arr:
        maxnum = max(maxnum, num)
        cnt[num] += 1
    print(solve(k, maxnum), end='')


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
