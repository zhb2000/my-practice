//分割回文串
//https://leetcode-cn.com/problems/palindrome-partitioning/
//DFS 枚举，DP 判回文串
struct Solution;


impl Solution {
    pub fn partition(s: String) -> Vec<Vec<String>> {
        let s: Vec<char> = s.chars().collect();
        let mut results: Vec<Vec<String>> = vec![];
        let mut temp: Vec<String> = vec![];
        let mut dp: Vec<Vec<Option<bool>>> = vec![vec![None; s.len() + 1]; s.len() + 1];
        Self::dfs(&mut results, &mut temp, &mut dp, &s, 0);
        return results;
    }

    fn is_hui(s: &[char], dp: &mut Vec<Vec<Option<bool>>>,
              start: usize, stop: usize) -> bool {
        assert!(start < stop);
        if stop - start == 1 {
            return true;
        }
        if stop - start == 2 {
            return s[start] == s[stop - 1];
        }
        match dp[start][stop] {
            Some(b) => return b,
            None => {
                let b = (s[start] == s[stop - 1]) &&
                    Self::is_hui(s, dp, start + 1, stop - 1);
                dp[start][stop] = Some(b);
                return b;
            }
        };
    }

    fn dfs(results: &mut Vec<Vec<String>>, temp: &mut Vec<String>,
           dp: &mut Vec<Vec<Option<bool>>>,
           s: &[char], start: usize) {
        let stop = s.len();
        if start == stop { // empty
            results.push(temp.clone());
            return;
        }
        for r in (start + 1)..=stop {
            if Self::is_hui(s, dp, start, r) {
                temp.push(s[start..r].iter().collect());
                Self::dfs(results, temp, dp, s, r);
                temp.pop();
            }
        }
    }
}

fn main() {
    //[["a","a","b"],["aa","b"]]
    println!("{:?}", Solution::partition("aab".to_string()));
    //[["a"]]
    println!("{:?}", Solution::partition("a".to_string()));
}


#[allow(dead_code)]
fn lower_bound<T: PartialOrd>(elements: &[T], value: &T) -> usize {
    let mut l = 0;
    let mut r = elements.len();
    while l < r {
        let m = l + ((r - l) >> 1);
        if elements[m] >= *value {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

#[allow(dead_code)]
fn upper_bound<T: PartialOrd>(elements: &[T], value: &T) -> usize {
    let mut l = 0;
    let mut r = elements.len();
    while l < r {
        let m = l + ((r - l) >> 1);
        if elements[m] <= *value {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}
