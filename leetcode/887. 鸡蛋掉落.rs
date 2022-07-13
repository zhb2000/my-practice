// 887. 鸡蛋掉落
// https://leetcode.cn/problems/super-egg-drop/
// DP（记忆化搜索）、决策单调性、二分
struct Solution;

use std::cmp::{max, min};
use std::collections::HashMap;

impl Solution {
    fn f(k: i32, n: i32, cache: &mut HashMap<(i32, i32), i32>) -> i32 {
        if k == 1 {
            return n;
        }
        if n == 0 {
            return 0;
        }
        if !cache.contains_key(&(k, n)) {
            let mut l = 1;
            let mut r = n;
            // [l, r]
            while r - l > 1 {
                let m = l + ((r - l) >> 1);
                let a = Self::f(k - 1, m - 1, cache);
                let b = Self::f(k, n - m, cache);
                if a > b {
                    r = m;
                } else if a < b {
                    l = m;
                } else {
                    l = m;
                    r = m;
                }
            }
            let maybe_ans1 = max(Self::f(k - 1, l - 1, cache), Self::f(k, n - l, cache));
            let maybe_ans2 = max(Self::f(k - 1, r - 1, cache), Self::f(k, n - r, cache));
            let ans = 1 + min(maybe_ans1, maybe_ans2);
            cache.insert((k, n), ans);
        }
        return cache[&(k, n)];
    }

    pub fn super_egg_drop(k: i32, n: i32) -> i32 {
        return Self::f(k, n, &mut HashMap::new());
    }
}

fn main() {
    assert_eq!(Solution::super_egg_drop(1, 2), 2);
    assert_eq!(Solution::super_egg_drop(2, 6), 3);
    assert_eq!(Solution::super_egg_drop(3, 14), 4);
    assert_eq!(Solution::super_egg_drop(2, 1), 1);
    assert_eq!(Solution::super_egg_drop(2, 2), 2);
}