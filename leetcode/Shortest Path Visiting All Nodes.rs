//Shortest Path Visiting All Nodes
//https://leetcode-cn.com/problems/shortest-path-visiting-all-nodes/
//TSP 问题、状压 DP、Floyd
struct Solution;

use std::cmp::min;

const INF: i32 = 1e9 as i32;

impl Solution {
    pub fn shortest_path_length(graph: Vec<Vec<i32>>) -> i32 {
        let n = graph.len();
        let full_status = (1 << n) - 1;
        let mut dist = vec![vec![INF; n]; n]; // dist[i][j]
        let mut f = vec![vec![INF; full_status + 1]; n]; // f[i][status]

        //init dist
        for (u, nei) in graph.iter().enumerate() {
            for &v in nei.iter() {
                dist[u][v as usize] = 1;
            }
        }
        for u in 0..n {
            dist[u][u] = 0;
        }

        //floyd
        for k in 0..n {
            for i in 0..n {
                for j in 0..n {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        //tsp
        for status in 0..=full_status {
            for i in 0..n {
                if status == 1 << i {
                    f[i][status] = 0;
                    continue;
                }
                for j in 0..n {
                    if j != i && Self::getbit(status, j) {
                        f[i][status] = min(f[i][status],
                                           f[j][Self::clearbit(status, i)] + dist[j][i]);
                    }
                }
            }
        }

        let mut ans = f[0][full_status];
        for i in 1..n {
            ans = min(ans, f[i][full_status]);
        }
        assert_ne!(ans, INF);
        return ans;
    }

    fn getbit(s: usize, i: usize) -> bool { s & (1 << i) != 0 }

    fn clearbit(s: usize, i: usize) -> usize { s & !(1 << i) }

    #[allow(dead_code)]
    fn stat_s(s: usize, n: usize) -> String {
        let mut string = "".to_string();
        for i in (0..n).rev() {
            string.push(if Self::getbit(s, i) { '1' } else { '0' });
        }
        return string;
    }
}

fn main() {
    assert_eq!(Solution::shortest_path_length(
        vec![vec![1, 2, 3], vec![0], vec![0], vec![0]]),
               4);
    assert_eq!(Solution::shortest_path_length(
        vec![vec![1], vec![0, 2, 4], vec![1, 3, 4], vec![2], vec![1, 2]]),
               4);
    assert_eq!(Solution::shortest_path_length(
        vec![vec![1, 2], vec![0, 3], vec![0, 3], vec![1, 2]]),
               3);
}
