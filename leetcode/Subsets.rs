//Subsets
//子集枚举（二进制法）
struct Solution;

impl Solution {
    pub fn subsets(nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut results = vec![];
        let n = nums.len();
        for status in 0..(1 << n) {
            let mut temp = vec![];
            for i in 0..n {
                if Self::getbit(status, i) {
                    temp.push(nums[i]);
                }
            }
            results.push(temp);
        }
        return results;
    }

    fn getbit(s: usize, i: usize) -> bool { s & (1 << i) != 0 }
}

fn main() {
    println!("{:?}", Solution::subsets(vec![1, 2, 3]));
    println!("{:?}", Solution::subsets(vec![0]));
}
