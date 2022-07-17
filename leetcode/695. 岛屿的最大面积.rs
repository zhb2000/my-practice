// 695. 岛屿的最大面积
// https://leetcode.cn/problems/max-area-of-island/
// DFS
struct Solution;

use std::cmp::max;

impl Solution {
    pub fn max_area_of_island(grid: Vec<Vec<i32>>) -> i32 {
        let m = grid.len();
        let n = grid[0].len();
        let mut vis = vec![false; m * n];
        let mut ans = 0;
        for i in 0..m {
            for j in 0..n {
                if grid[i][j] == 1 && !vis[i * n + j] {
                    ans = max(ans, Self::dfs(i as i32, j as i32, &grid, &mut vis));
                }
            }
        }
        return ans;
    }

    fn dfs(i: i32, j: i32, grid: &Vec<Vec<i32>>, vis: &mut [bool]) -> i32 {
        let m = grid.len() as i32;
        let n = grid[0].len() as i32;
        vis[(i * n + j) as usize] = true;
        let mut ans = 1;
        for (x, y) in [(i - 1, j), (i, j + 1), (i + 1, j), (i, j - 1)] {
            if (0..m).contains(&x) && (0..n).contains(&y)
                && grid[x as usize][y as usize] == 1 && !vis[(x * n + y) as usize] {
                ans += Self::dfs(x, y, grid, vis);
            }
        }
        return ans;
    }
}

fn main() {
    assert_eq!(Solution::max_area_of_island(vec![vec![0, 1, 1, 0, 1, 0, 0, 0]]), 2);
    assert_eq!(Solution::max_area_of_island(vec![vec![0, 0, 0, 0, 0, 0, 0, 0]]), 0);
}