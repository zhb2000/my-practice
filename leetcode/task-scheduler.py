# 任务调度器
# 滑动窗口、贪心
# https://leetcode-cn.com/classic/problems/task-scheduler/description/
import math
import sys
import collections
import random
import heapq
import typing
from math import sqrt, ceil, floor, fabs, sin, cos
from typing import List, Tuple, Set, Dict, Iterable, Deque, TypeVar
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


T = TypeVar('T')


def counter_dict(seq: Iterable[T]) -> Dict[T, int]:
    counter = {}
    for x in seq:
        if x not in counter:
            counter[x] = 1
        else:
            counter[x] += 1
    return counter


# find a task not in win and has max count
def select_task(counter: Dict[str, int], in_win: Set[str]) -> str:
    result = None
    cnt = -1
    for task in counter:
        if task not in in_win and counter[task] > cnt:
            result = task
            cnt = counter[task]
    return result


class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        counter = counter_dict(tasks)
        win_size = n + 1
        cur_size = 0
        in_win = set()
        win = deque()
        time_sum = 0
        while len(counter) != 0:
            if cur_size == win_size:
                if win[0] != '0':
                    in_win.remove(win[0])
                win.popleft()
            task = select_task(counter, in_win)
            if task is None:  # no such task
                win.append('0')
            else:
                win.append(task)
                in_win.add(task)
                counter[task] -= 1
                if counter[task] == 0:
                    counter.pop(task)
            time_sum += 1
            if cur_size < win_size:
                cur_size += 1
        return time_sum


def main():
    tasks = ["A", "A", "A", "B", "B", "B"]
    n = 2
    print(Solution().leastInterval(tasks, n))


if __name__ == '__main__':
    sys.setrecursionlimit(int(1e5))
    if LOCAL:
        in_file = open('in.txt', 'r')
        out_file = open('out.txt', 'w')
        sys.stdin = in_file
        sys.stdout = out_file
    main()
