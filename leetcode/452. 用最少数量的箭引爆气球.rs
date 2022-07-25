// 452. 用最少数量的箭引爆气球
// https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/
// 排序、贪心
// 两种不同做法。按 start 还是 end 排序？从第一个开始还是从最后一个开始？取 start 还是 end 作为射箭点？
// 这里用的是按 start 排序、从最后一个开始、取 start 作为射箭点
struct Solution;

impl Solution {
    pub fn find_min_arrow_shots(points: Vec<Vec<i32>>) -> i32 {
        let mut points: Vec<(i32, i32)> = points.iter().map(|v| (v[0], v[1])).collect();
        points.sort();
        // last 表示上一个区间的射箭点，last 必是某区间的左端点
        let mut last = points.last().unwrap().0;
        let mut count = 1;
        for &(start, end) in points.iter().rev() {
            if end < last {
                count += 1;
                last = start;
            }
        }
        return count;
    }
}

fn main() {
    assert_eq!(Solution::find_min_arrow_shots(vec![vec![10, 16], vec![2, 8], vec![1, 6], vec![7, 12]]), 2);
    assert_eq!(Solution::find_min_arrow_shots(vec![vec![1, 2], vec![3, 4], vec![5, 6], vec![7, 8]]), 4);
    assert_eq!(Solution::find_min_arrow_shots(vec![vec![1, 2], vec![2, 3], vec![3, 4], vec![4, 5]]), 2);
}