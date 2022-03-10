// 最长的美好子字符串
// https://leetcode-cn.com/problems/longest-nice-substring/
// 枚举子串两端、位运算 (bitset)
struct Solution;

impl Solution {
    pub fn longest_nice_substring(s: String) -> String {
        let s: Vec<char> = s.chars().collect();
        let mut pos = 0;
        let mut len = 0;
        for i in 0..s.len() {
            let mut lowers = 0;
            let mut uppers = 0;
            // 在枚举子串两端的同时维护并校验合法性，时间复杂度从 O(n^3) 降为 O(n^2)
            for j in i..s.len() {
                // [i, j]
                if s[j].is_lowercase() {
                    lowers = Solution::setbit(lowers, Solution::lower_index(s[j]));
                } else {
                    uppers = Solution::setbit(uppers, Solution::upper_index(s[j]));
                }
                if lowers == uppers && j - i + 1 > len {
                    len = j - i + 1;
                    pos = i
                }
            }
        }
        return s[pos..(pos + len)].iter().collect();
    }

    fn setbit(s: usize, i: usize) -> usize { s | (1 << i) }

    fn lower_index(ch: char) -> usize { ch as usize - 'a' as usize }

    fn upper_index(ch: char) -> usize { ch as usize - 'A' as usize }
}

fn main() {
    assert_eq!(Solution::longest_nice_substring("aAa".to_string()), "aAa");
    assert_eq!(Solution::longest_nice_substring("YazaAay".to_string()), "aAa");
    assert_eq!(Solution::longest_nice_substring("Bb".to_string()), "Bb");
    assert_eq!(Solution::longest_nice_substring("c".to_string()), "");
    assert_eq!(Solution::longest_nice_substring("dDzeE".to_string()), "dD");
}
