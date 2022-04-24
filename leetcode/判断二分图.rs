// DFS 判断二分图
// https://leetcode-cn.com/problems/is-graph-bipartite/

struct Solution;


impl Solution {
    pub fn is_bipartite(graph: Vec<Vec<i32>>) -> bool {
        let n = graph.len();
        let mut colors = vec![0; n];
        for u in 0..n {
            if colors[u] == 0 {
                colors[u] = 1;
                if !Solution::check(u, &graph, &mut colors) {
                    return false;
                }
            }
        }
        return true;
    }

    fn check(u: usize, graph: &Vec<Vec<i32>>, colors: &mut [i32]) -> bool {
        for v in graph[u].iter() {
            let v = *v as usize;
            if colors[v] == 0 {
                colors[v] = -colors[u];
                if !Solution::check(v, &graph, colors) {
                    return false;
                }
            } else if colors[v] != -colors[u] {
                assert_eq!(colors[v], colors[u]);
                return false;
            }
        }
        return true;
    }
}

fn main() {
    assert_eq!(
        Solution::is_bipartite(
            vec![vec![1, 2, 3], vec![0, 2], vec![0, 1, 3], vec![0, 2]]
        ),
        false
    );
    assert_eq!(
        Solution::is_bipartite(
            vec![vec![1, 3], vec![0, 2], vec![1, 3], vec![0, 2]]
        ),
        true
    );
}
