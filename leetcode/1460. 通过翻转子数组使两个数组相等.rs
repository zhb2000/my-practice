// 1460. 通过翻转子数组使两个数组相等
// https://leetcode.cn/problems/make-two-arrays-equal-by-reversing-sub-arrays/
// 思维题
// 只要两个数组包含相同的元素，就必能通过翻转使它们相等
impl Solution {
    pub fn can_be_equal(mut target: Vec<i32>, mut arr: Vec<i32>) -> bool {
        target.sort();
        arr.sort();
        return target == arr;
    }
}
