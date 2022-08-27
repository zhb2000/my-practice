// 869. 重新排序得到 2 的幂
// https://leetcode.cn/problems/reordered-power-of-2/
// 预处理出所有合法的方案，方案用每个数字的个数来表示
struct Solution;

use std::collections::HashSet;

impl Solution {
    pub fn reordered_power_of2(n: i32) -> bool {
        fn digit_counter(mut n: i32) -> [i32; 10] {
            let mut counter = [0; 10];
            while n > 0 {
                let digit = n % 10;
                counter[digit as usize] += 1;
                n /= 10;
            }
            return counter;
        }

        // 2^29 < 10^9 < 2^30
        let set: HashSet<[i32; 10]> = (0..30)
            .map(|i| 1 << i)
            .map(digit_counter)
            .collect();
        return set.contains(&digit_counter(n));
    }
}

fn main() {
    assert!(Solution::reordered_power_of2(1));
    assert!(!Solution::reordered_power_of2(10));
}
