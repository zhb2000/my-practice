// 27. 移除元素
// https://leetcode-cn.com/problems/remove-element/
// 双指针
// 将要删除的元素 swap 到末尾。不保证输出数组按原始顺序。
struct Solution;

impl Solution {
    pub fn remove_element(nums: &mut Vec<i32>, val: i32) -> i32 {
        // [0, n)
        let mut l = 0; // [0, l) checked
        let mut r = nums.len(); // [r, n) vals
        while l < r {
            if nums[l] == val {
                r -= 1;
                let temp = nums[l];
                nums[l] = nums[r];
                nums[r] = temp;
            } else {
                l += 1;
            }
        }
        assert_eq!(l, r);
        return l as i32;
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
