// 363. 矩形区域不超过 K 的最大数值和
// https://leetcode.cn/problems/max-sum-of-rectangle-no-larger-than-k/
// 前缀和、有序集合、二分查找
// 本题跟其他“矩阵和”类题目的套路一样，枚举上下边界，二位前缀和转一维前缀和，此外本题还需要使用有序集合 + 二分查找来降低复杂度，时间复杂度 O(n^2mlogm)
struct Solution;

use std::cmp::max;
use std::collections::BTreeSet;

impl Solution {
    pub fn max_sum_submatrix(matrix: Vec<Vec<i32>>, k: i32) -> i32 {
        let n = matrix.len();
        let m = matrix[0].len();
        let mut ans = i32::MIN;
        let mut v = vec![0; m];
        let mut set = BTreeSet::<i32>::new();
        for r1 in 0..n {
            v.fill(0);
            for r2 in r1..n { // rows of range [r1, r2]
                for c in 0..m {
                    v[c] += matrix[r2][c];
                }
                let mut prefix_sum = 0; // prefix_sum
                set.clear();
                set.insert(prefix_sum);
                for &value in v.iter() {
                    prefix_sum += value;
                    // prefix_sum - a <= k, so a >= prefix_sum - k
                    if let Some(&a) = set.range((prefix_sum - k)..).next() { // smallest a
                        ans = max(ans, prefix_sum - a);
                    }
                    set.insert(prefix_sum);
                }
            }
        }
        return ans;
    }
}

fn main() {
    assert_eq!(Solution::max_sum_submatrix(
        vec![vec![1, 0, 1],
             vec![0, -2, 3]],
        2), 2);
    assert_eq!(Solution::max_sum_submatrix(vec![vec![2, 2, -1]], 3), 3);
}
