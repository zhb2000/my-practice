// 684. 冗余连接
// https://leetcode-cn.com/problems/redundant-connection/
// 并查集

struct Solution;

use std::mem::swap;

struct UnionFindSet {
    father: Vec<usize>,
    size: Vec<usize>,
}

impl UnionFindSet {
    fn new(n: usize) -> Self {
        UnionFindSet {
            father: (0..n).collect(),
            size: vec![1; n],
        }
    }

    fn find(&mut self, u: usize) -> usize {
        if self.father[u] == u {
            return u;
        } else {
            self.father[u] = self.find(self.father[u]);
            return self.father[u];
        }
    }

    fn in_same(&mut self, u: usize, v: usize) -> bool {
        self.find(u) == self.find(v)
    }

    fn union(&mut self, u: usize, v: usize) {
        if self.in_same(u, v) {
            return;
        }
        let mut uu = self.find(u);
        let mut vv = self.find(v);
        if self.size[uu] > self.size[vv] {
            swap(&mut uu, &mut vv);
        }
        // uu.size <= vv.size, put uu into vv
        self.father[uu] = vv;
        self.size[vv] += self.size[uu];
    }
}

impl Solution {
    pub fn find_redundant_connection(edges: Vec<Vec<i32>>) -> Vec<i32> {
        let n = edges.len();
        let mut uf = UnionFindSet::new(n + 1);
        let mut ans = (0, 0); // 最后一条加入后不会减少联通分量个数的边即为答案
        for edge in edges.iter() {
            let u = edge[0] as usize;
            let v = edge[1] as usize;
            if uf.in_same(u, v) {
                ans = (u, v);
            } else {
                uf.union(u, v);
            }
        }
        return vec![ans.0 as i32, ans.1 as i32];
    }
}

fn main() {
    assert_eq!(
        Solution::find_redundant_connection(
            vec![vec![1, 2], vec![1, 3], vec![2, 3]]
        ),
        vec![2, 3]
    );
    assert_eq!(
        Solution::find_redundant_connection(
            vec![vec![1, 2], vec![2, 3], vec![3, 4], vec![1, 4], vec![1, 5]]
        ),
        vec![1, 4]
    );
}
