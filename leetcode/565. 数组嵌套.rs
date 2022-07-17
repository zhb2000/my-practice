// 565. 数组嵌套
// https://leetcode.cn/problems/array-nesting/
// 图、思维题
// 图中最长环的长度
struct Solution;

use std::cmp::max;

impl Solution {
    pub fn array_nesting(nums: Vec<i32>) -> i32 {
        let mut vis = vec![false; nums.len()];
        let mut ans = 1;
        for &i in nums.iter() {
            if vis[i as usize] {
                continue;
            }
            vis[i as usize] = true;
            let mut temp = 1;
            let mut p = nums[i as usize];
            while p != i {
                assert!(!vis[p as usize]);
                vis[p as usize] = true;
                temp += 1;
                p = nums[p as usize];
            }
            ans = max(ans, temp);
        }
        return ans;
    }
}

fn main() {
    assert_eq!(Solution::array_nesting(vec![5, 4, 0, 3, 1, 6, 2]), 4);
}