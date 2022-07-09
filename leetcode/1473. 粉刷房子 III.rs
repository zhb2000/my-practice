// 1473. 粉刷房子 III
// https://leetcode.cn/problems/paint-house-iii/
// 三维 DP
struct Solution;

use std::cmp::min;

// f(i, j, k) 表示房子 i 的颜色为 j，且房子 0 到 i 组成了 k 个街区
impl Solution {
    pub fn min_cost(houses: Vec<i32>, cost: Vec<Vec<i32>>, m: i32, n: i32, target: i32) -> i32 {
        const INF: i32 = 1e8 as i32;
        let m = m as usize;
        let n = n as usize;
        let target = target as usize;
        let mut f = vec![vec![vec![INF; target + 1]; n]; m]; // f[m][n][target+1]
        for j in 0..n {
            if houses[0] == 0 {
                f[0][j][1] = cost[0][j];
            } else if houses[0] - 1 == j as i32 {
                f[0][j][1] = 0;
            }
        }
        // println!("f[0]:\n{:?}\n", f[0]);
        for i in 1..m {
            for j in 0..n {
                for k in 1..=target {
                    if houses[i] == 0 {
                        let mut temp = INF;
                        for pre in 0..n {
                            if pre == j {
                                temp = min(temp, f[i - 1][pre][k] + cost[i][j]);
                            } else {
                                temp = min(temp, f[i - 1][pre][k - 1] + cost[i][j]);
                            }
                        }
                        f[i][j][k] = temp;
                    } else if houses[i] - 1 == j as i32 {
                        let mut temp = INF;
                        for pre in 0..n {
                            if pre == j {
                                temp = min(temp, f[i - 1][pre][k]);
                            } else {
                                temp = min(temp, f[i - 1][pre][k - 1]);
                            }
                        }
                        f[i][j][k] = temp;
                    } else {
                        f[i][j][k] = INF;
                    }
                }
            }
            // println!("f[{i}]:\n{:?}\n", f[i]);
        }
        let mut ans = INF;
        for color in 0..n {
            ans = min(ans, f[m - 1][color][target]);
        }
        return if ans != INF { ans } else { -1 };
    }
}

fn main() {
    assert_eq!(Solution::min_cost(
        vec![1, 2],
        vec![
            vec![1, 10],
            vec![10, 1],
        ],
        2, 2, 2,
    ), 0);

    assert_eq!(Solution::min_cost(
        vec![0, 0, 0, 0, 0],
        vec![
            vec![1, 10],
            vec![10, 1],
            vec![10, 1],
            vec![1, 10],
            vec![5, 1],
        ],
        5, 2, 3,
    ), 9);

    assert_eq!(Solution::min_cost(
        vec![0, 2, 1, 2, 0],
        vec![
            vec![1, 10],
            vec![10, 1],
            vec![10, 1],
            vec![1, 10],
            vec![5, 1],
        ],
        5, 2, 3,
    ), 11);

    assert_eq!(Solution::min_cost(
        vec![0, 0, 0, 0, 0],
        vec![
            vec![1, 10],
            vec![10, 1],
            vec![1, 10],
            vec![10, 1],
            vec![1, 10],
        ],
        5, 2, 5,
    ), 5);

    assert_eq!(Solution::min_cost(
        vec![3, 1, 2, 3],
        vec![
            vec![1, 1, 1],
            vec![1, 1, 1],
            vec![1, 1, 1],
            vec![1, 1, 1],
        ],
        4, 3, 3,
    ), -1);
}