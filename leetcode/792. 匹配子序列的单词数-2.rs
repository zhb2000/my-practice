// 792. 匹配子序列的单词数
// https://leetcode.cn/problems/number-of-matching-subsequences/
// 主串只遍历一次
struct Solution;

impl Solution {
    pub fn num_matching_subseq(s: String, words: Vec<String>) -> i32 {
        fn str2vec(s: &str) -> Vec<usize> {
            s.chars().map(|c| c as usize - 'a' as usize).collect()
        }
        let s = str2vec(&s);
        let words: Vec<Vec<usize>> = words.iter().map(|s| str2vec(s)).collect();
        let mut map: [Vec<&[usize]>; 26] = [(); 26].map(|_| vec![]);
        for word in words.iter() {
            map[word[0]].push(word);
        }
        let mut count = 0;
        for &ch in s.iter() {
            let current = map[ch].clone();
            map[ch].clear();
            for &word in current.iter() {
                if word.len() == 1 {
                    count += 1;
                } else { // word.len() > 1
                    map[word[1]].push(&word[1..]);
                }
            }
        }
        return count;
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