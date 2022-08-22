// 593. 有效的正方形
// https://leetcode.cn/problems/valid-square/
// 计算几何
struct Solution;

#[derive(Copy, Clone, Eq, PartialEq)]
struct Vector {
    x: i32,
    y: i32,
}

impl Vector {
    fn new(from: (i32, i32), to: (i32, i32)) -> Self { Vector { x: to.0 - from.0, y: to.1 - from.1 } }

    fn len2(&self) -> i32 { self.x * self.x + self.y * self.y }
}

impl std::ops::Mul for Vector {
    type Output = i32;

    fn mul(self, rhs: Self) -> Self::Output { self.x * rhs.x + self.y * rhs.y }
}

impl std::ops::Add for Vector {
    type Output = Vector;

    fn add(self, rhs: Self) -> Self::Output { Vector { x: self.x + rhs.x, y: self.y + rhs.y } }
}

impl Solution {
    pub fn valid_square(p1: Vec<i32>, p2: Vec<i32>, p3: Vec<i32>, p4: Vec<i32>) -> bool {
        let p1 = (p1[0], p1[1]);
        let p2 = (p2[0], p2[1]);
        let p3 = (p3[0], p3[1]);
        let p4 = (p4[0], p4[1]);
        let mut v = [Vector::new(p1, p2), Vector::new(p1, p3), Vector::new(p1, p4)];
        v.sort_by_key(Vector::len2);
        return v[0].len2() > 0
            && v[0].len2() == v[1].len2()
            && v[0] * v[1] == 0
            && v[0] + v[1] == v[2];
    }
}

fn main() {
    assert!(Solution::valid_square(vec![0, 0], vec![1, 1], vec![1, 0], vec![0, 1]));
    assert!(!Solution::valid_square(vec![0, 0], vec![1, 1], vec![1, 0], vec![0, 12]));
    assert!(Solution::valid_square(vec![1, 0], vec![-1, 0], vec![0, 1], vec![0, -1]));
    assert!(!Solution::valid_square(vec![0, 0], vec![0, 0], vec![0, 0], vec![0, 0]));
}
