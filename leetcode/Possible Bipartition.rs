//Possible Bipartition
//https://leetcode-cn.com/problems/possible-bipartition/
//种类并查集
struct Solution;

use std::mem::swap;

struct UnionFindSet {
    fa: Vec<i32>,
    sz: Vec<i32>,
}

impl UnionFindSet {
    fn new(n: i32) -> Self {
        let mut uf = UnionFindSet {
            fa: vec![0; n as usize + 1],
            sz: vec![1; n as usize + 1],
        };
        for (i, father) in uf.fa.iter_mut().enumerate() {
            *father = i as i32;
        }
        return uf;
    }

    fn find(&mut self, u: i32) -> i32 {
        if self.fa[u as usize] == u {
            return u;
        }
        self.fa[u as usize] = self.find(self.fa[u as usize]);
        return self.fa[u as usize];
    }

    fn in_same(&mut self, u: i32, v: i32) -> bool {
        return self.find(u) == self.find(v);
    }

    fn union(&mut self, u: i32, v: i32) {
        if self.in_same(u, v) {
            return;
        }
        let mut uu = self.find(u);
        let mut vv = self.find(v);
        if self.sz[uu as usize] < self.sz[vv as usize] {
            swap(&mut uu, &mut vv);
        }
        self.sz[uu as usize] += self.sz[vv as usize];
        self.fa[vv as usize] = uu;
    }
}

impl Solution {
    pub fn possible_bipartition(n: i32, dislikes: Vec<Vec<i32>>) -> bool {
        let mut uf = UnionFindSet::new((n + 5) * 2);
        for pair in dislikes.iter() {
            let (a, b) = (pair[0], pair[1]);
            if uf.in_same(a, b) {
                return false;
            }
            uf.union(a, n + b);
            uf.union(n + a, b);
        }
        return true;
    }
}

fn main() {
    assert_eq!(Solution::possible_bipartition(
        4, vec![vec![1, 2], vec![1, 3], vec![2, 4]]),
               true);
    assert_eq!(Solution::possible_bipartition(
        3, vec![vec![1, 2], vec![1, 3], vec![2, 3]]),
               false);
    assert_eq!(Solution::possible_bipartition(
        5, vec![vec![1, 2], vec![2, 3], vec![3, 4], vec![4, 5], vec![1, 5]]),
               false);
}
