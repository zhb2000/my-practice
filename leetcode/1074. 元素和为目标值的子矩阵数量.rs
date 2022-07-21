// 1074. 元素和为目标值的子矩阵数量
// https://leetcode.cn/problems/number-of-submatrices-that-sum-to-target/
// 一维前缀和、哈希表
// 把子矩阵看成条带，用一维前缀和的方法做
struct Solution;

use std::collections::HashMap;
use std::iter::FromIterator;

impl Solution {
    pub fn num_submatrix_sum_target(matrix: Vec<Vec<i32>>, target: i32) -> i32 {
        let n = matrix.len();
        let m: usize = matrix[0].len();
        let mut presums = vec![vec![0; m + 1]; n + 1];
        for i in 1..=n {
            for j in 1..=m {
                presums[i][j] = matrix[i - 1][j - 1] + presums[i][j - 1];
            }
        }
        for i in 1..=n {
            for j in 1..=m {
                presums[i][j] = presums[i][j] + presums[i - 1][j];
            }
        }
        let mut ans = 0;
        for i1 in 1..=n {
            for i2 in i1..=n {
                let presum = Self::minus(&presums[i2], &presums[i1 - 1]);
                let mut map = HashMap::new();
                map.insert(0, 1); // presum[0] = 0
                for &x in presum[1..].iter() {
                    if let Some(cnt) = map.get(&(x - target)) {
                        ans += cnt;
                    }
                    map.entry(x).or_insert(0);
                    map.insert(x, map[&x] + 1);
                }
            }
        }
        return ans;
    }

    fn minus(v1: &[i32], v2: &[i32]) -> Vec<i32> {
        Vec::from_iter(v1.iter().zip(v2.iter()).map(|(x, y)| x - y))
    }
}

fn main() {
    assert_eq!(Solution::num_submatrix_sum_target(
        vec![
            vec![1, 1],
            vec![1, 1],
        ],
        4), 1);
    assert_eq!(Solution::num_submatrix_sum_target(
        vec![
            vec![0, 1, 0],
            vec![1, 1, 1],
            vec![0, 1, 0],
        ],
        0), 4);
    assert_eq!(Solution::num_submatrix_sum_target(
        vec![
            vec![1, -1],
            vec![-1, 1],
        ],
        0), 5);
    assert_eq!(Solution::num_submatrix_sum_target(
        vec![vec![904]],
        0), 0);
}