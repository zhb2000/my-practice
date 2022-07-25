// 74. 搜索二维矩阵
// https://leetcode.cn/problems/search-a-2d-matrix/
// 二分查找
struct Solution;

impl Solution {
    pub fn search_matrix(matrix: Vec<Vec<i32>>, target: i32) -> bool {
        let n = matrix.len();
        let m = matrix[0].len();
        let seq = |i: usize| matrix[i / m][i % m];
        let mut l = 0;
        let mut r = n * m;
        while l < r {
            let m = l + ((r - l) >> 1);
            use std::cmp::Ordering::*;
            match seq(m).cmp(&target) {
                Equal => return true,
                Less => l = m + 1,
                Greater => r = m
            }
        }
        return false;
    }
}

fn main() {
    assert!(Solution::search_matrix(
        vec![
            vec![1, 3, 5, 7],
            vec![10, 11, 16, 20],
            vec![23, 30, 34, 60],
        ],
        3,
    ));
    assert!(!Solution::search_matrix(
        vec![
            vec![1, 3, 5, 7],
            vec![10, 11, 16, 20],
            vec![23, 30, 34, 60],
        ],
        13,
    ));
}
