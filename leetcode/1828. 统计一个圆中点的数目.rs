// 1828. 统计一个圆中点的数目
// 遍历、几何
struct Solution;

impl Solution {
    pub fn count_points(points: Vec<Vec<i32>>, queries: Vec<Vec<i32>>) -> Vec<i32> {
        let mut answer = vec![];
        for (x0, y0, r) in queries.iter().map(|q| (q[0], q[1], q[2])) {
            let r2 = r * r;
            let mut ans = 0;
            for (x1, y1) in points.iter().map(|p| (p[0], p[1])) {
                let dx = x0 - x1;
                let dy = y0 - y1;
                let d2 = dx * dx + dy * dy;
                if d2 <= r2 {
                    ans += 1;
                }
            }
            answer.push(ans);
        }
        return answer;
    }
}

fn main() {
    assert_eq!(Solution::count_points(
        vec![vec![1, 3], vec![3, 3], vec![5, 3], vec![2, 2]],
        vec![vec![2, 3, 1], vec![4, 3, 1], vec![1, 1, 2]],
    ), vec![3, 2, 2]);
    assert_eq!(Solution::count_points(
        vec![vec![1, 1], vec![2, 2], vec![3, 3], vec![4, 4], vec![5, 5]],
        vec![vec![1, 2, 2], vec![2, 2, 2], vec![4, 3, 2], vec![4, 3, 3]],
    ), vec![2, 3, 2, 4]);
}
