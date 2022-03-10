// 26. 删除有序数组中的重复项
// https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/
// 重复赋值法（双指针）
struct Solution;

impl Solution {
    pub fn remove_duplicates(nums: &mut Vec<i32>) -> i32 {
        let mut new_len = 0;
        for i in 0..nums.len() {
            if i == 0 || nums[i] > nums[i - 1] {
                nums[new_len] = nums[i];
                new_len += 1;
            }
        }
        nums.truncate(new_len);
        return new_len as i32;
    }
}

fn main() {
    let mut nums = vec![1, 1, 2];
    assert_eq!(Solution::remove_duplicates(&mut nums), 2);
    assert_eq!(nums, vec![1, 2]);

    nums = vec![0, 0, 1, 1, 1, 2, 2, 3, 3, 4];
    assert_eq!(Solution::remove_duplicates(&mut nums), 5);
    assert_eq!(nums, vec![0, 1, 2, 3, 4]);
}
