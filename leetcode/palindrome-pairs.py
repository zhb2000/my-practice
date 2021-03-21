# 336. 回文对
# https://leetcode-cn.com/classic/problems/palindrome-pairs/description/
# 子串哈希做法
from typing import List, Dict, Set, Tuple, Iterable
import math

MAX_LEN = 300 + 5
BASE = 101
MOD = int(1e9 + 7)

base_n = [0 for _ in range(MAX_LEN)]


class PrefixHash:
    def __init__(self, s: str):
        self.s = s
        self.h = [0 for _ in range(len(s))]
        for i in range(len(s)):
            si = ord(s[i]) - ord('a') + 1
            if i == 0:
                self.h[i] = si % MOD
            else:
                self.h[i] = (self.h[i - 1] * BASE + si) % MOD

    def subhash(self, l: int, r: int) -> int:
        if r < l:
            return 0
        if l == 0:
            return self.h[r]
        return (self.h[r] - self.h[l - 1] * base_n[r - l + 1] % MOD + MOD) % MOD

    def hash(self) -> int:
        return self.subhash(0, len(self.s) - 1)


class WordEntry:
    def __init__(self, s: str):
        self.h = PrefixHash(s)
        self.rh = PrefixHash(s[::-1])
        self.n = len(s)


class Solution:
    def __init__(self):
        # calc base_n
        base_n[0] = 1
        for i in range(1, MAX_LEN):
            base_n[i] = base_n[i - 1] * BASE % MOD

    def palindromePairs(self, words: List[str]) -> List[List[int]]:
        entries = []
        hash_dict = {}
        rev_hash_dict = {}
        for i, s in enumerate(words):
            w = WordEntry(s)
            entries.append(w)
            # DEBUG begin
            # print(f's: {s}, h: {w.h.hash()}')
            # print(f'rs: {s[::-1]}, h: {w.rh.hash()}')
            # assert w.h.hash() not in hash_dict
            # assert w.rh.hash() not in rev_hash_dict
            # DEBUG end
            hash_dict[w.h.hash()] = i
            rev_hash_dict[w.rh.hash()] = i
        ans_set = set()
        for i, w in enumerate(entries):
            n = w.n
            if w.h.hash() in rev_hash_dict:
                j = rev_hash_dict[w.h.hash()]
                if j != i:
                    ans_set.add((i, j))
            x = 1
            while 2 * x <= n:
                h1 = w.rh.subhash(0, x - 1)
                h2 = w.h.subhash(n - 2 * x, n - x - 1)
                if h1 != h2:
                    x += 1
                    continue
                h3 = w.h.subhash(0, n - 2 * x - 1)
                if h3 in rev_hash_dict:
                    j = rev_hash_dict[h3]
                    if j != i:
                        ans_set.add((i, j))
                x += 1
            x = 1
            while 2 * x <= n:
                h1 = w.h.subhash(0, x - 1)
                h2 = w.rh.subhash(n - 2 * x, n - x - 1)
                if h1 != h2:
                    x += 1
                    continue
                h3 = w.rh.subhash(0, n - 2 * x - 1)
                if h3 in hash_dict:
                    j = hash_dict[h3]
                    if j != i:
                        ans_set.add((j, i))
                x += 1
            x = 0
            while 2 * x + 1 <= n:
                h1 = w.rh.subhash(0, x + 1 - 1 - 1)
                h2 = w.h.subhash(n - 2 * x - 1, n - x - 1 - 1)
                if h1 != h2:
                    x += 1
                    continue
                h3 = w.h.subhash(0, n - 2 * x - 1 - 1)
                if h3 in rev_hash_dict:
                    j = rev_hash_dict[h3]
                    if j != i:
                        ans_set.add((i, j))
                x += 1
            x = 0
            while 2 * x + 1 <= n:
                h1 = w.h.subhash(0, x + 1 - 1 - 1)
                h2 = w.rh.subhash(n - 2 * x - 1, n - x - 1 - 1)
                if h1 != h2:
                    x += 1
                    continue
                h3 = w.rh.subhash(0, n - 2 * x - 1 - 1)
                if h3 in hash_dict:
                    j = hash_dict[h3]
                    if j != i:
                        ans_set.add((j, i))
                x += 1
        return [list(pair) for pair in ans_set]


if __name__ == '__main__':
    # words = ["abcd", "dcba", "lls", "s", "sssll"]
    words = ["bat", "tab", "cat"]
    # words = ["a", ""]
    print(Solution().palindromePairs(words))
