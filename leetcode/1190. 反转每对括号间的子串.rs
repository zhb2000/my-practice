// 1190. 反转每对括号间的子串
// https://leetcode.cn/problems/reverse-substrings-between-each-pair-of-parentheses/
// DFS、栈
struct Solution;

impl Solution {
    pub fn reverse_parentheses(s: String) -> String {
        let s: Vec<char> = s.chars().collect();
        let mut paired = vec![0; s.len()];
        let mut stack = vec![];
        for (i, &ch) in s.iter().enumerate() {
            if ch == '(' {
                stack.push(i);
            } else if ch == ')' {
                let j = stack.pop().unwrap();
                paired[j] = i;
                paired[i] = j;
            }
        }
        let mut out = vec![];
        Self::output(&s, 0, s.len() - 1, false, &mut out, &paired);
        return out.iter().collect();
    }

    fn output(s: &[char], l: usize, r: usize, reverse: bool, out: &mut Vec<char>, paired: &Vec<usize>) {
        if reverse {
            assert_ne!(l, 0);
            let mut i = r;
            while i >= l {
                if s[i] == ')' {
                    assert_eq!(s[paired[i]], '(');
                    Self::output(s, paired[i] + 1, i - 1, false, out, paired);
                    i = paired[i] - 1;
                } else {
                    assert_ne!(s[i], '(');
                    out.push(s[i]);
                    i -= 1;
                }
            }
        } else {
            let mut i = l;
            while i <= r {
                if s[i] == '(' {
                    assert_eq!(s[paired[i]], ')');
                    Self::output(s, i + 1, paired[i] - 1, true, out, paired);
                    i = paired[i] + 1;
                } else {
                    assert_ne!(s[i], ')');
                    out.push(s[i]);
                    i += 1;
                }
            }
        }
    }
}

fn main() {
    assert_eq!(Solution::reverse_parentheses("(abcd)".to_string()), "dcba");
    assert_eq!(Solution::reverse_parentheses("(u(love)i)".to_string()), "iloveu");
    assert_eq!(Solution::reverse_parentheses("(ed(et(oc))el)".to_string()), "leetcode");
    assert_eq!(Solution::reverse_parentheses("a(bcdefghijkl(mno)p)q".to_string()), "apmnolkjihgfedcbq");
}