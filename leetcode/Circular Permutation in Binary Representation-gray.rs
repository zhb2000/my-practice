//Circular Permutation in Binary Representation
//https://leetcode-cn.com/problems/circular-permutation-in-binary-representation/
//格雷码（构造法）
//一个格雷码数组，异或上同一个数，依然是格雷码数组

struct Solution;

impl Solution {
    pub fn circular_permutation(n: i32, start: i32) -> Vec<i32> {
        let mut result: Vec<i32> = vec![];
        result.reserve(1 << n);
        for i in 0..(1 << n) {
            let gray = i ^ (i >> 1);
            result.push(gray ^ start);
        }
        return result;
    }
}

fn main() {
    println!("{:?}", Solution::circular_permutation(2, 3));
    println!("{:?}", Solution::circular_permutation(3, 2));
}
