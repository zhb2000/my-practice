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


def main():
    weight_of = [1, 2, 3, 5, 10, 20]
    num_of = read_ints()
    assert len(num_of) == 6
    ans_set = {0}
    for weight, num in zip(weight_of, num_of):
        this_set = set()
        for use in range(1, num + 1):
            for w in ans_set:
                new_w = w + use * weight
                if new_w not in ans_set and new_w not in this_set:
                    this_set.add(new_w)
        ans_set.update(this_set)
    print(f'Total={len(ans_set) - 1}')


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
