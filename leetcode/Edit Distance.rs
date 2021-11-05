//Edit Distance
//https://leetcode-cn.com/problems/edit-distance/
//线性 DP
struct Solution;

impl Solution {
    pub fn min_distance(word1: String, word2: String) -> i32 {
        let mut s1 = vec!['\0'];
        s1.extend(word1.chars());
        let mut s2 = vec!['\0'];
        s2.extend(word2.chars());
        return Self::solve(&s1, &s2);
    }

    fn solve(s1: &[char], s2: &[char]) -> i32 {
        let n = s1.len() - 1;
        let m = s2.len() - 1;
        let mut f = vec![vec![0; m + 1]; n + 1];//f[n+1][m+1]
        for i in 1..=n {
            f[i][0] = i as i32;
        }
        for j in 1..=m {
            f[0][j] = j as i32;
        }
        for i in 1..=n {
            for j in 1..=m {
                let a = f[i][j - 1] + 1;
                let b = f[i - 1][j] + 1;
                let c = f[i - 1][j - 1] + if s1[i] == s2[j] { 0 } else { 1 };
                f[i][j] = *[a, b, c].iter().min().unwrap();
            }
        }
        return f[n][m];
    }
}

fn main() {
    assert_eq!(Solution::min_distance("horse".to_string(),
                                      "ros".to_string()),
               3);
    assert_eq!(Solution::min_distance("intention".to_string(),
                                      "execution".to_string()),
               5);
}
