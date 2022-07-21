// 792. 匹配子序列的单词数
// https://leetcode.cn/problems/number-of-matching-subsequences/
// 朴素做法 + 哈希去重
struct Solution;

use std::collections::HashMap;

impl Solution {
    pub fn num_matching_subseq(s: String, words: Vec<String>) -> i32 {
        let mut map = HashMap::new();
        let mut count = 0;
        for word in words.iter() {
            let result = if let Some(&result) = map.get(word) {
                result
            } else {
                let result = Self::is_subsequence(word, &s);
                map.insert(word, result);
                result
            };
            if result {
                count += 1;
            }
        }
        return count;
    }

    fn is_subsequence(s1: &str, s2: &str) -> bool {
        let mut p1 = s1.chars().peekable();
        for ch in s2.chars() {
            p1.next_if_eq(&ch);
        }
        return p1.next().is_none();
    }
}

fn main() {
    assert_eq!(Solution::num_matching_subseq(
        "abcde".to_string(),
        vec!["a".to_string(), "bb".to_string(), "acd".to_string(), "ace".to_string()],
    ), 3);
    assert_eq!(Solution::num_matching_subseq(
        "dsahjpjauf".to_string(),
        vec!["ahjpjau".to_string(), "ja".to_string(), "ahbwzgqnuk".to_string(), "tnmlanowax".to_string()],
    ), 2);
}