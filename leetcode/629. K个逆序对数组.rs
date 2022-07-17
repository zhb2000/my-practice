// 629. K个逆序对数组
// https://leetcode.cn/problems/k-inverse-pairs-array/
// DP、滚动数组
struct Solution;

impl Solution {
    pub fn k_inverse_pairs(n: i32, k: i32) -> i32 {
        const MOD: i32 = 1e9 as i32 + 7;
        let (n, k) = (n as usize, k as usize);
        let mut f = vec![0; k + 1];
        f[0] = 1; // f[1][0]
        for i in 2..=n {
            for j in (0..=k).rev() {
                if j == 0 {
                    f[j] = 1;
                } else {
                    let mut sum = 0;
                    for x in 0..=i - 1 {
                        if x > j {
                            break;
                        }
                        sum = (sum + f[j - x]) % MOD; // f[n-1][k-x]
                    }
                    f[j] = sum;
                }
            }
        }
        return f[k];
    }
}

fn main() {
    assert_eq!(Solution::k_inverse_pairs(3, 0), 1);
    assert_eq!(Solution::k_inverse_pairs(3, 1), 2);
    assert_eq!(Solution::k_inverse_pairs(2, 1), 1);
    assert_eq!(Solution::k_inverse_pairs(3, 2), 2);
}