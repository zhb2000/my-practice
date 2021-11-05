//Longest Happy Prefix
//https://leetcode-cn.com/problems/longest-happy-prefix/
//KMP，前缀函数
struct Solution;

impl Solution {
    pub fn longest_prefix(s: String) -> String {
        let text: Vec<char> = s.chars().collect();
        let pi = Self::calc_pi(&text);
        let len = *pi.last().unwrap();
        return text[0..len].iter().collect();
    }

    fn calc_pi(s: &[char]) -> Vec<usize> {
        let n = s.len();
        let mut pi: Vec<usize> = vec![0; n];
        for i in 1..n {
            let mut j = pi[i - 1];//len, also pos to compare
            while j > 0 && s[j] != s[i] {
                j = pi[j - 1];
            }
            if s[j] == s[i] {
                pi[i] = j + 1;
            }
        }
        return pi;
    }
}

fn main() {
    assert_eq!(Solution::longest_prefix("level".to_string()), "l");
    assert_eq!(Solution::longest_prefix("ababab".to_string()), "abab");
    assert_eq!(Solution::longest_prefix("leetcodeleet".to_string()), "leet");
    assert_eq!(Solution::longest_prefix("a".to_string()), "");
}
