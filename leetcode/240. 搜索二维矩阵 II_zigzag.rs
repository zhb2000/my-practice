// 240. 搜索二维矩阵 II
// https://leetcode.cn/problems/search-a-2d-matrix-ii/
// 按折线路径顺序查找，保证横纵坐标单调变化
struct Solution;

impl Solution {
    pub fn search_matrix(matrix: Vec<Vec<i32>>, target: i32) -> bool {
        let n = matrix.len();
        let m = matrix[0].len();
        let mut i = 0;
        let mut j = m - 1;
        while i < n && j as isize >= 0 {
            use std::cmp::Ordering::*;
            match matrix[i][j].cmp(&target) {
                Equal => return true,
                Greater => j = (j as isize - 1) as usize,
                Less => i += 1
            }
        }
        return false;
    }
}

fn main() {
    assert!(Solution::search_matrix(
        vec![
            vec![1, 4, 7, 11, 15],
            vec![2, 5, 8, 12, 19],
            vec![3, 6, 9, 16, 22],
            vec![10, 13, 14, 17, 24],
            vec![18, 21, 23, 26, 30],
        ],
        5,
    ));
    assert!(!Solution::search_matrix(
        vec![
            vec![1, 4, 7, 11, 15],
            vec![2, 5, 8, 12, 19],
            vec![3, 6, 9, 16, 22],
            vec![10, 13, 14, 17, 24],
            vec![18, 21, 23, 26, 30]],
        20,
    ));
    assert!(!Solution::search_matrix(vec![vec![5]], 2));
    assert!(!Solution::search_matrix(vec![vec![-5]], 2));
    assert!(Solution::search_matrix(
        vec![
            vec![2, 5],
            vec![2, 8],
            vec![7, 9],
            vec![7, 11],
            vec![9, 11],
        ],
        7,
    ));
}
