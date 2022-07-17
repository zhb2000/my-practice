// 576. 出界的路径数
// https://leetcode.cn/problems/out-of-boundary-paths/
// DP、滚动数组
struct Solution;

impl Solution {
    pub fn find_paths(m: i32, n: i32, max_move: i32, start_row: i32, start_column: i32) -> i32 {
        const MOD: i32 = 1e9 as i32 + 7;
        if max_move == 0 {
            return 0;
        }
        let mut f = vec![vec![0; n as usize]; m as usize]; // f[m][n]
        for _ in 1..=max_move {
            let last = f.clone();
            for i in 0..m {
                for j in 0..n {
                    let mut a = 0;
                    if i == 0 { a += 1; }
                    if i == m - 1 { a += 1; }
                    if j == 0 { a += 1; }
                    if j == n - 1 { a += 1; }
                    for (x, y) in [(i - 1, j), (i, j + 1), (i + 1, j), (i, j - 1)] {
                        if (0..m).contains(&x) && (0..n).contains(&y) {
                            a = (a + last[x as usize][y as usize]) % MOD;
                        }
                    }
                    f[i as usize][j as usize] = a;
                }
            }
        }
        return f[start_row as usize][start_column as usize];
    }
}

fn main() {
    assert_eq!(Solution::find_paths(2, 2, 2, 0, 0), 6);
    assert_eq!(Solution::find_paths(1, 3, 3, 0, 1), 12);
}