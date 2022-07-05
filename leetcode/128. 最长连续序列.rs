// 128. 最长连续序列
// https://leetcode.cn/problems/longest-consecutive-sequence/
// 哈希表
struct Solution;

use std::cmp::max;
use std::collections::HashMap;

impl Solution {
    pub fn longest_consecutive(nums: Vec<i32>) -> i32 {
        let mut m: HashMap<i32, bool> = nums.iter().map(|x| (*x, false)).collect();
        let mut ans = 0;
        for x in nums.iter() {
            if *m.get(x).unwrap() {
                continue;
            }
            *m.get_mut(x).unwrap() = true;
            let mut cnt = 1;
            let mut num = x + 1;
            while m.contains_key(&num) {
                *m.get_mut(&num).unwrap() = true;
                cnt += 1;
                num += 1;
            }
            ans = max(ans, cnt);
        }
        return ans;
    }
}

fn main() {
    assert_eq!(Solution::longest_consecutive(vec![100, 4, 200, 1, 3, 2]), 4);
    assert_eq!(Solution::longest_consecutive(vec![0, 3, 7, 2, 5, 8, 4, 6, 0, 1]), 9);
}