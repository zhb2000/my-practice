// 330. 按要求补齐数组
// https://leetcode.cn/problems/patching-array/
// 贪心、思维题、数学
struct Solution;

impl Solution {
    pub fn min_patches(nums: Vec<i32>, n: i32) -> i32 {
        let mut ans = 0;
        let mut r = 0; // can cover [1, r] now
        let mut i = 0;
        while r < n as i64 {
            match nums.get(i).map(|&num| num as i64) {
                Some(num) if num <= r + 1 => {
                    r += num;
                    i += 1;
                }
                _ => {
                    ans += 1; // cannot cover r+1, so add r+1 into nums
                    r += r + 1;
                }
            }
        }
        return ans;
    }
}

fn main() {
    assert_eq!(Solution::min_patches(vec![1, 3], 6), 1);
    assert_eq!(Solution::min_patches(vec![1, 5, 10], 20), 2);
    assert_eq!(Solution::min_patches(vec![1, 2, 2], 5), 0);
    assert_eq!(Solution::min_patches(vec![1, 2, 31, 33], 2147483647), 28);
}
