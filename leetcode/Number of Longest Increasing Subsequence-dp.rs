//Number of Longest Increasing Subsequence
//https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/
//线性 DP，时间复杂度 O(n^2)
struct Solution;

impl Solution {
    pub fn find_number_of_lis(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        let mut f = vec![1; n]; //len
        let mut g = vec![1; n]; //num
        for i in 0..n {
            for j in 0..i {
                if nums[j] < nums[i] {
                    if f[j] + 1 > f[i] {
                        f[i] = f[j] + 1;
                        g[i] = g[j];
                    } else if f[j] + 1 == f[i] {
                        g[i] += g[j];
                    }
                }
            }
        }

        // println!("f: {:?}", f);
        // println!("g: {:?}", g);

        let mut max_len = 1;
        let mut num = 0;
        for i in 0..n {
            if f[i] > max_len {
                max_len = f[i];
                num = g[i];
            } else if f[i] == max_len {
                num += g[i];
            }
        }
        return num;
    }
}

fn main() {
    assert_eq!(Solution::find_number_of_lis(vec![1, 3, 5, 4, 7]), 2);
    assert_eq!(Solution::find_number_of_lis(vec![2, 2, 2, 2, 2]), 5);
    assert_eq!(Solution::find_number_of_lis(vec![2]), 1);
    assert_eq!(Solution::find_number_of_lis(vec![]), 0);
    assert_eq!(Solution::find_number_of_lis(vec![1, 2, 4, 3, 5, 4, 7, 2]), 3);
    //1 2 4 5 7; 1 2 3 5 7; 1 2 3 4 7
    assert_eq!(Solution::find_number_of_lis(vec![1, 1, 1, 2, 2, 2, 3, 3, 3]), 27);
}
