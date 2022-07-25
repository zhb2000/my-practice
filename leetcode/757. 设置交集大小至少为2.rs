// 757. 设置交集大小至少为2
// https://leetcode.cn/problems/set-intersection-size-at-least-two/
// 排序、贪心
// 思路和做法类似 452. 用最少数量的箭引爆气球
struct Solution;

impl Solution {
    pub fn intersection_size_two(intervals: Vec<Vec<i32>>) -> i32 {
        let mut intervals: Vec<(i32, i32)> = intervals.iter().map(|v| (v[0], v[1])).collect();
        intervals.sort();
        // last1 和 last2 表示上一个区间在交集中的两个元素，last1 必是某区间的左端点
        let mut last1 = intervals.last().unwrap().0;
        let mut last2 = last1 + 1;
        let mut count = 2;
        for &(start, end) in intervals.iter().rev() {
            if end < last1 {
                count += 2;
                last1 = start;
                last2 = start + 1;
            } else if last1 <= end && end < last2 {
                count += 1;
                if start == last1 {
                    last1 = start;
                    last2 = start + 1;
                } else {
                    assert!(start < last1);
                    last2 = last1;
                    last1 = start;
                }
            }
        }
        return count;
    }
}

fn main() {
    assert_eq!(Solution::intersection_size_two(vec![vec![1, 3], vec![1, 4], vec![2, 5], vec![3, 5]]), 3);
    assert_eq!(Solution::intersection_size_two(vec![vec![1, 2], vec![2, 3], vec![2, 4], vec![4, 5]]), 5);
}