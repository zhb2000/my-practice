// 27. 移除元素
// https://leetcode-cn.com/problems/remove-element/
// 将要保留的元素赋值到对应位置。保证输出数组按原始顺序。
struct Solution;

impl Solution {
    pub fn remove_element(nums: &mut Vec<i32>, val: i32) -> i32 {
        let mut j = 0; // [0, j) is the new vector
        for i in 0..nums.len() {
            if nums[i] != val {
                nums[j] = nums[i];
                j += 1;
            }
        }
        return j as i32;
    }
}

fn main() {
    let mut nums = vec![3, 2, 2, 3];
    assert_eq!(Solution::remove_element(&mut nums, 3), 2);
    println!("{:?}", nums);

    nums = vec![0, 1, 2, 2, 3, 0, 4, 2];
    assert_eq!(Solution::remove_element(&mut nums, 2), 5);
    println!("{:?}", nums);

    nums = vec![1];
    assert_eq!(Solution::remove_element(&mut nums, 1), 0);
    println!("{:?}", nums);

    nums = vec![1];
    assert_eq!(Solution::remove_element(&mut nums, 0), 1);
    println!("{:?}", nums);
}
