// 97. 交错字符串
// https://leetcode.cn/problems/interleaving-string/
// 二维线性 DP + 滚动数组优化
struct Solution;

impl Solution {
    pub fn is_interleave(s1: String, s2: String, s3: String) -> bool {
        let s1: Vec<char> = s1.chars().collect();
        let s2: Vec<char> = s2.chars().collect();
        let s3: Vec<char> = s3.chars().collect();
        if s1.len() + s2.len() != s3.len() {
            return false;
        }

        // f(0, 0) = true
        // f(0, j) = f(0, j-1) and s2[j-1] == s3[j-1]
        // f(i, 0) = f(i-1, 0) and s1[i-1] == s3[i-1]
        // f(i, j) = (f(i-1, j) and s1[i-1] == s3[i+j-1]) or (f(i, j-1) and s2[j-1] == s3[i+j-1])

        let mut f = vec![false; s2.len() + 1];
        f[0] = true; // f[0][0]
        for j in 1..=s2.len() { // f[0][j]
            f[j] = f[j - 1] && s2[j - 1] == s3[j - 1];
        }
        for i in 1..=s1.len() {
            f[0] = f[0] && s1[i - 1] == s3[i - 1]; // f[i][0]
            for j in 1..=s2.len() { // f[i][j]
                f[j] = (f[j] && s1[i - 1] == s3[i + j - 1])
                    || (f[j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
        return f[s2.len()];
    }
}

fn main() {
    assert!(Solution::is_interleave("a".to_string(), "b".to_string(), "ab".to_string()));
    assert!(Solution::is_interleave("aabcc".to_string(), "dbbca".to_string(), "aadbbcbcac".to_string()));
    assert!(!Solution::is_interleave("aabcc".to_string(), "dbbca".to_string(), "aadbbbaccc".to_string()));
    assert!(Solution::is_interleave("".to_string(), "".to_string(), "".to_string()));
}