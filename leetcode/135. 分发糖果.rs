// 135. 分发糖果
// https://leetcode.cn/problems/candy/
// 思维题
// 先从左到右扫一遍，再从右到左扫一遍
struct Solution;

use std::cmp::max;

impl Solution {
    pub fn candy(ratings: Vec<i32>) -> i32 {
        let n = ratings.len();
        let mut ans = vec![1; n];
        for i in 0..n {
            if i > 0 && ratings[i] > ratings[i - 1] {
                ans[i] = max(ans[i], ans[i - 1] + 1);
            }
        }
        for i in (0..n).rev() {
            if i < n - 1 && ratings[i] > ratings[i + 1] {
                ans[i] = max(ans[i], ans[i + 1] + 1);
            }
        }
        return ans.iter().sum();
    }
}

fn main() {
    assert_eq!(Solution::candy(vec![1, 0, 2]), 5);
    assert_eq!(Solution::candy(vec![1, 2, 2]), 4);
}