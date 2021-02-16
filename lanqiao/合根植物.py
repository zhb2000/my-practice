import math
import sys
from typing import List, Tuple, Set, Dict
from math import sqrt, ceil, floor, fabs, sin, cos

LOCAL = False
# LOCAL = True


class UnionFind:
    def __init__(self, max_size: int):
        self.max_size = max_size
        self.fa = [i for i in range(max_size + 1)]
        self.size = [1 for _ in range(max_size + 1)]

    def clear(self, topn: int):
        for i in range(topn + 1):
            self.fa[i] = i
            self.size[i] = 1

    def find(self, x: int) -> int:
        if self.fa[x] == x:
            return x
        else:
            self.fa[x] = self.find(self.fa[x])
            return self.fa[x]

    def union(self, x: int, y: int):
        if self.in_same(x, y):
            return
        xx = self.find(x)
        yy = self.find(y)
        if self.size[yy] > self.size[xx]:
            xx, yy = yy, xx
        self.fa[yy] = xx
        self.size[xx] += self.size[yy]

    def in_same(self, x: int, y: int) -> bool:
        return self.find(x) == self.find(y)


def read_int_list() -> List[int]:
    return list(map(int, read_list()))


def read_list() -> List[str]:
    return input().split(' ')


def main():
    m, n = read_int_list()
    m: int
    n: int
    k = read_int_list()[0]
    uf = UnionFind(m * n + 5)
    cnt: int = m * n
    for _ in range(k):
        a, b = read_int_list()
        a: int
        b: int
        if not uf.in_same(a, b):
            uf.union(a, b)
            cnt -= 1
    print(cnt, end='')


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        with open('in.txt', 'r') as in_file, open('out.txt', 'w') as out_file:
            sys.stdin = in_file
            sys.stdout = out_file
            main()
    else:
        main()
