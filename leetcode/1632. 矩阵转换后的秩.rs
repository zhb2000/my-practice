// 1632. 矩阵转换后的秩
// https://leetcode.cn/problems/rank-transform-of-a-matrix/
// 并查集
// 节点合并容易写错：需要使用并查集将值相同的节点合并、先全部合并完再找节点的前驱
struct Solution;

struct UnionFind {
    size: Vec<usize>,
    fa: Vec<usize>,
}

impl UnionFind {
    fn new(size: usize) -> Self {
        UnionFind {
            size: vec![1; size],
            fa: (0..size).collect(),
        }
    }

    fn find(&mut self, x: usize) -> usize {
        if self.fa[x] != x {
            self.fa[x] = self.find(self.fa[x]);
        }
        return self.fa[x];
    }

    fn union(&mut self, x: usize, y: usize) {
        let x = self.find(x);
        let y = self.find(y);
        let (x, y) = if self.size[x] > self.size[y] { (x, y) } else { (y, x) };
        self.fa[y] = x;
        self.size[x] += self.size[y];
    }
}

impl Solution {
    pub fn matrix_rank_transform(matrix: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let n = matrix.len();
        let m = matrix[0].len();
        let c2u = |i: usize, j: usize| i * m + j;

        let mut sorted_rows: Vec<Vec<(usize, i32)>> = vec![];
        for i in 0..n {
            let mut row: Vec<(usize, i32)> = matrix[i]
                .iter()
                .copied()
                .enumerate()
                .collect();
            row.sort_by_key(|(_j, x)| *x);
            sorted_rows.push(row);
        }
        let mut sorted_columns: Vec<Vec<(usize, i32)>> = vec![];
        for j in 0..m {
            let mut column: Vec<(usize, i32)> = (0..n)
                .map(|i| matrix[i][j])
                .enumerate()
                .collect();
            column.sort_by_key(|(_i, x)| *x);
            sorted_columns.push(column);
        }

        let mut uf = UnionFind::new(n * m);
        for (i, row) in sorted_rows.iter().enumerate() {
            for window in row.windows(2) {
                let (pj, px) = window[0];
                let (j, x) = window[1];
                if px == x {
                    uf.union(c2u(i, j), c2u(i, pj));
                }
            }
        }
        for (j, columns) in sorted_columns.iter().enumerate() {
            for window in columns.windows(2) {
                let (pi, px) = window[0];
                let (i, x) = window[1];
                if px == x {
                    uf.union(c2u(i, j), c2u(pi, j));
                }
            }
        }

        // pre[u] contains nodes which is before u
        let mut pre: Vec<Vec<usize>> = vec![vec![]; n * m];
        for (i, row) in sorted_rows.iter().enumerate() {
            for window in row.windows(2) {
                let (pj, px) = window[0];
                let (j, x) = window[1];
                if px < x {
                    let pu = uf.find(c2u(i, pj));
                    let u = uf.find(c2u(i, j));
                    pre[u].push(pu);
                }
            }
        }
        for (j, columns) in sorted_columns.iter().enumerate() {
            for window in columns.windows(2) {
                let (pi, px) = window[0];
                let (i, x) = window[1];
                if px < x {
                    let pu = uf.find(c2u(pi, j));
                    let u = uf.find(c2u(i, j));
                    pre[u].push(pu)
                }
            }
        }

        let mut ans = vec![0; n * m];
        for u in 0..(n * m) {
            ans[u] = Solution::dfs(uf.find(u), &mut ans, &pre);
        }
        let mut ans2 = vec![vec![0; m]; n];
        for i in 0..n {
            for j in 0..m {
                ans2[i][j] = ans[c2u(i, j)];
            }
        }
        return ans2;
    }

    fn dfs(u: usize, ans: &mut Vec<i32>, pre: &Vec<Vec<usize>>) -> i32 {
        if ans[u] > 0 {
            return ans[u];
        }
        let pre_rank = pre[u]
            .iter()
            .map(|&v| Solution::dfs(v, ans, pre))
            .max()
            .unwrap_or(0);
        ans[u] = pre_rank + 1;
        return ans[u];
    }
}

fn main() {
    assert_eq!(
        Solution::matrix_rank_transform(vec![
            vec![-37, -50, -3, 44],
            vec![-37, 46, 13, -32],
            vec![47, -42, -3, -40],
            vec![-17, -22, -39, 24],
        ]),
        vec![
            vec![2, 1, 4, 6],
            vec![2, 6, 5, 4],
            vec![5, 2, 4, 3],
            vec![4, 3, 1, 5],
        ]
    );
    // [[2, 1, 3, 6],
    // [2, 6, 5, 4],
    // [5, 2, 3, 3],
    // [4, 3, 1, 5]]


    assert_eq!(
        Solution::matrix_rank_transform(vec![
            vec![1, 2],
            vec![3, 4],
        ]),
        vec![
            vec![1, 2],
            vec![2, 3],
        ]
    );
    assert_eq!(
        Solution::matrix_rank_transform(vec![
            vec![7, 7],
            vec![7, 7],
        ]),
        vec![
            vec![1, 1],
            vec![1, 1],
        ]
    );
    assert_eq!(
        Solution::matrix_rank_transform(vec![
            vec![20, -21, 14],
            vec![-19, 4, 19],
            vec![22, -47, 24],
            vec![-19, 4, 19],
        ]),
        vec![
            vec![4, 2, 3],
            vec![1, 3, 4],
            vec![5, 1, 6],
            vec![1, 3, 4],
        ]
    );
    assert_eq!(
        Solution::matrix_rank_transform(vec![
            vec![7, 3, 6],
            vec![1, 4, 5],
            vec![9, 8, 2]]),
        vec![
            vec![5, 1, 4],
            vec![1, 2, 3],
            vec![6, 3, 1],
        ]
    );
}
