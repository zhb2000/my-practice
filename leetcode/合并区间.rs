struct Solution;

use std::cmp::max;

impl Solution {
    pub fn merge(mut intervals: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        intervals.sort_unstable_by(|a, b| a[0].cmp(&b[0]));
        let mut result = vec![];
        let mut cur_left = intervals[0][0];
        let mut cur_right = intervals[0][1];
        for pair in intervals.iter() {
            let l = pair[0];
            let r = pair[1];
            if l <= cur_right {
                cur_right = max(cur_right, r);
            } else {
                result.push(vec![cur_left, cur_right]);
                cur_left = l;
                cur_right = r;
            }
        }
        result.push(vec![cur_left, cur_right]);
        return result;
    }
}

fn main() {
    println!("{:?}", Solution::merge(
        vec![vec![1, 3], vec![2, 6], vec![8, 10], vec![15, 18]]));
    println!("{:?}", Solution::merge(
        vec![vec![1, 4], vec![4, 5]]));
}
