// 719. 找出第 K 小的数对距离
// https://leetcode.cn/problems/find-k-th-smallest-pair-distance/
// 排序 + 二分答案 + 尺取
struct Solution;

use std::cmp::Ordering;

impl Solution {
    fn lower_bound_answer<F: FnMut(i32) -> Ordering>(mut l: i32, mut r: i32, mut check: F) -> i32 {
        // [l, r)
        while l < r {
            let m = l + (r - l) / 2;
            match check(m) {
                Ordering::Greater | Ordering::Equal => r = m,
                _ => l = m + 1
            }
        }
        return l;
    }

    pub fn smallest_distance_pair(mut nums: Vec<i32>, k: i32) -> i32 {
        nums.sort();
        return Self::lower_bound_answer(0, nums[nums.len() - 1] - nums[0], |sum| {
            let mut cnt = 0;
            let mut l = 0;
            // [l, r]
            // 本题中的尺取：依次枚举右端点，对每个右端点不断移动左端点
            for r in 1..nums.len() {
                while nums[r] - nums[l] > sum {
                    l += 1;
                }
                cnt += r - l;
            }
            return (cnt as i32).cmp(&k);
        });
    }
}

fn main() {
    assert_eq!(Solution::smallest_distance_pair(vec![1, 3, 1], 1), 0);
    assert_eq!(Solution::smallest_distance_pair(vec![1, 1, 1], 2), 0);
    assert_eq!(Solution::smallest_distance_pair(vec![1, 6, 1], 3), 5);
    assert_eq!(Solution::smallest_distance_pair(vec![9, 10, 7, 10, 6, 1, 5, 4, 9, 8], 18), 2);
}
