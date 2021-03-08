# 最大子矩阵
# https://leetcode-cn.com/problems/max-submatrix-lcci/
from typing import List


class Solution:
    def __init__(self):
        maxn = 200 + 5
        self.mat = [[0 for j in range(maxn + 3)] for i in range(maxn + 3)]
        self.pre_sum = [[0 for j in range(maxn + 3)] for i in range(maxn + 3)]

    def getMaxMatrix(self, matrix: List[List[int]]) -> List[int]:
        n = len(matrix)
        m = len(matrix[0])
        for i in range(1, n + 1):
            for j in range(1, m + 1):
                self.mat[i][j] = matrix[i - 1][j - 1]
        self.calc_pre_sum(n, m)
        up, down, left, right = self.solve(n, m)
        return [up - 1, left - 1, down - 1, right - 1]

    def col_sum(self, j: int, up: int, down: int) -> int:
        return self.pre_sum[down][j] - self.pre_sum[up - 1][j]

    def calc_pre_sum(self, n: int, m: int):
        for j in range(1, m + 1):
            for i in range(1, n + 1):
                self.pre_sum[i][j] = self.mat[i][j] + self.pre_sum[i - 1][j]

    def solve(self, n: int, m: int):
        ans = None
        ans_up = 0
        ans_down = 0
        ans_left = 0
        ans_right = 0
        for up in range(1, n + 1):
            for down in range(up, n + 1):
                sum_arr = [0 for i in range(m + 1)]
                for j in range(1, m + 1):
                    sum_arr[j] = sum_arr[j - 1] + self.col_sum(j, up, down)
                sum_arr_min = 0
                sum_arr_min_j = 0
                temp_ans = None
                temp_ans_left = 0
                temp_ans_right = 0
                for j in range(1, m + 1):
                    the_ans = sum_arr[j] - sum_arr_min
                    if temp_ans is None or the_ans > temp_ans:
                        temp_ans = the_ans
                        temp_ans_left = sum_arr_min_j + 1
                        temp_ans_right = j
                    if sum_arr[j] < sum_arr_min:
                        sum_arr_min = sum_arr[j]
                        sum_arr_min_j = j
                if ans is None or temp_ans > ans:
                    ans = temp_ans
                    ans_up = up
                    ans_down = down
                    ans_left = temp_ans_left
                    ans_right = temp_ans_right
        return ans_up, ans_down, ans_left, ans_right


if __name__ == '__main__':
    matrix = [
        [-1, 0],
        [0, -1]
    ]
    matrix = [[-1]]
    matrix = [[-4, -5]]
    print(Solution().getMaxMatrix(matrix))
    pass
