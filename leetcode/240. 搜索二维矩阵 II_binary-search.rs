// 240. 搜索二维矩阵 II
// https://leetcode.cn/problems/search-a-2d-matrix-ii/
// 二分查找
struct Solution;

impl Solution {
    pub fn search_matrix(matrix: Vec<Vec<i32>>, target: i32) -> bool {
        let rows = |r: usize| {
            let matrix = &matrix;
            return move |c: usize| matrix[r][c];
        };
        let cols = |c: usize| {
            let matrix = &matrix;
            return move |r: usize| matrix[r][c];
        };
        let mut r1 = 0;
        let mut c1 = 0;
        let mut r2 = matrix.len();
        let mut c2 = matrix[0].len();
        let mut op = 0;
        while r1 < r2 && c1 < c2 {
            if op == 0 {
                let j = Self::lower_bound(rows(r1), c1, c2, target);
                if j < c2 && matrix[r1][j] == target {
                    return true;
                }
                assert!(j == c2 || matrix[r1][j] > target);
                c2 = j;
            } else if op == 1 {
                let i = Self::lower_bound(cols(c1), r1, r2, target);
                if i < r2 && matrix[i][c1] == target {
                    return true;
                }
                assert!(i == r2 || matrix[i][c1] > target);
                r2 = i;
            } else if op == 2 {
                let j = Self::lower_bound(rows(r2 - 1), c1, c2, target);
                if j < c2 && matrix[r2 - 1][j] == target {
                    return true;
                }
                assert!(j == c2 || matrix[r2 - 1][j] > target);
                c1 = j;
            } else {
                let i = Self::lower_bound(cols(c2 - 1), r1, r2, target);
                if i < r2 && matrix[i][c2 - 1] == target {
                    return true;
                }
                assert!(i == r2 || matrix[i][c2 - 1] > target);
                r1 = i;
            }
            op = (op + 1) % 4;
        }
        return false;
    }

    fn lower_bound(seq: impl Fn(usize) -> i32, mut start: usize, mut stop: usize, target: i32) -> usize {
        while start < stop {
            let m = start + ((stop - start) >> 1);
            if seq(m) >= target {
                stop = m;
            } else {
                start = m + 1;
            }
        }
        return start;
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
