// 540. 有序数组中的单一元素
// https://leetcode-cn.com/problems/single-element-in-a-sorted-array/
// 二分搜索
struct Solution;

use std::cmp::min;

// 独立数之前，相同两数的下标是偶数、奇数
// 独立数之后，相同两数的下标是奇数、偶数
impl Solution {
    pub fn single_non_duplicate(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        if n == 1 {
            return nums[0];
        }
        let mut l = 0;
        let mut r = n;
        // [l, r)
        while l < r {
            let m = l + (r - l) / 2;
            if m == 0 {
                if nums[0] == nums[1] {
                    l = 2;
                } else {
                    return nums[0];
                }
            } else if m == n - 1 {
                if nums[n - 2] == nums[n - 1] {
                    r = n - 2;
                } else {
                    return nums[n - 1];
                }
            } else {
                let i = if nums[m - 1] == nums[m] {
                    Some(m - 1)
                } else if nums[m + 1] == nums[m] {
                    Some(m + 1)
                } else {
                    None
                };
                if let Some(i) = i {
                    let first_index = min(m, i);
                    assert_eq!(nums[first_index], nums[first_index + 1]);
                    if first_index % 2 == 0 {
                        l = first_index + 2;
                    } else {
                        r = first_index;
                    }
                } else {
                    return nums[m];
                }
            }
        }
        assert!(false);
        return 0;
    }
}

fn main() {
    assert_eq!(Solution::single_non_duplicate(vec![1, 1, 2, 3, 3, 4, 4, 8, 8]), 2);
    assert_eq!(Solution::single_non_duplicate(vec![3, 3, 7, 7, 10, 11, 11]), 10);
    assert_eq!(Solution::single_non_duplicate(vec![1]), 1);
    assert_eq!(Solution::single_non_duplicate(vec![1, 1, 0]), 0);
    assert_eq!(Solution::single_non_duplicate(vec![0, 1, 1]), 0);
}
