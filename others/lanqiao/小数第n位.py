import math
import sys
from typing import List, Tuple, Set, Dict
from math import sqrt, ceil, floor, fabs, sin, cos

LOCAL, DEBUG = False, False


# LOCAL = True
# DEBUG = True

def read_strs() -> List[str]:
    return input().split(' ')


def read_ints() -> List[int]:
    return list(map(int, read_strs()))


def solve(a: int, b: int, n: int) -> List[int]:
    arr = [-1, -1, -1]
    temp2index: Dict[int, int] = {}
    index2ans = [-1]
    start = 1
    cir_len = 0
    rest = a % b
    for i in range(1, n + 2 + 1):
        temp = rest * 10
        if temp in temp2index.keys():
            start = temp2index[temp]
            cir_len = i - start
            break
        temp2index[temp] = i
        ans = temp // b
        rest = temp % b
        index2ans.append(ans)
        if i == n or i == n + 1 or i == n + 2:
            arr[i - n] = ans
    for i in range(0, 3):
        if arr[i] == -1:
            index = n + i
            j = (index - start) % cir_len + start
            arr[i] = index2ans[j]
    return arr


def main():
    a, b, n = read_ints()
    arr = solve(a, b, n)
    for digit in arr:
        print(digit, end='')


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
