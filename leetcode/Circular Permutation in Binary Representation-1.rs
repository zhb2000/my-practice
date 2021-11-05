//Circular Permutation in Binary Representation
//https://leetcode-cn.com/problems/circular-permutation-in-binary-representation/
//想象成一张有向图，显然，图中的每个节点都是等价的
//因此，随便选一个没走过的点走即可

struct Solution;

impl Solution {
    pub fn circular_permutation(n: i32, start: i32) -> Vec<i32> {
        let mut vis = vec![false; 1 << n];
        let mut result = vec![start];
        vis[start as usize] = true;
        let mut cur = start;
        while (result.len() as i32) < (1 << n) {
            cur = Self::next_not_visit(cur, n, &vis);
            assert_ne!(cur, -1);
            vis[cur as usize] = true;
            result.push(cur);
        }
        return result;
    }

    fn next_not_visit(cur: i32, n: i32, vis: &[bool]) -> i32 {
        for i in 0..n {
            let a = Self::change_bit(cur, i);
            if !vis[a as usize] {
                return a;
            }
        }
        return -1;
    }

    fn change_bit(num: i32, i: i32) -> i32 { num ^ (1 << i) }
}

fn main() {
    println!("{:?}", Solution::circular_permutation(2, 3));
    println!("{:?}", Solution::circular_permutation(3, 2));
}
