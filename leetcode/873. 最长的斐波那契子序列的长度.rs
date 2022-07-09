// 873. 最长的斐波那契子序列的长度
// https://leetcode.cn/problems/length-of-longest-fibonacci-subsequence/
// DP
struct Solution;

use std::cmp::max;
use std::collections::HashMap;

// f[i][x] 表示最后一个数为 arr[i]、倒数第二个数为 x 的斐波那契数列的最长长度
impl Solution {
    pub fn len_longest_fib_subseq(arr: Vec<i32>) -> i32 {
        let mut f: Vec<HashMap<i32, i32>> = vec![HashMap::new(); arr.len()];
        let mut ans = 2;
        for i in 1..arr.len() {
            for j in 0..i {
                let length = match f[j].get(&(arr[i] - arr[j])) {
                    Some(l) => l + 1,
                    None => 2
                };
                f[i].insert(arr[j], length);
                ans = max(ans, length);
            }
        }
        return if ans == 2 { 0 } else { ans };
    }
}

fn main() {
    assert_eq!(Solution::len_longest_fib_subseq(vec![1, 2, 3, 4, 5, 6, 7, 8]), 5);
    assert_eq!(Solution::len_longest_fib_subseq(vec![1, 3, 7, 11, 12, 14, 18]), 3);
    assert_eq!(Solution::len_longest_fib_subseq(vec![1, 3, 5]), 0);
}