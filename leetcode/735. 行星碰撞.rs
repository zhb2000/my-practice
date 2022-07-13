// 735. 行星碰撞
// https://leetcode.cn/problems/asteroid-collision/
// 思维题、栈
struct Solution;

use std::cmp::Ordering;

impl Solution {
    pub fn asteroid_collision(asteroids: Vec<i32>) -> Vec<i32> {
        let mut stack: Vec<i32> = vec![];
        for &x in asteroids.iter() {
            let mut push = true;
            if x < 0 {
                while !stack.is_empty() && stack.last().unwrap() > &0 {
                    let y = stack.pop().unwrap();
                    match x.abs().cmp(&y.abs()) {
                        Ordering::Greater => {}
                        Ordering::Less => {
                            push = false;
                            stack.push(y);
                            break;
                        }
                        Ordering::Equal => {
                            push = false;
                            break;
                        }
                    }
                }
            }
            if push {
                stack.push(x);
            }
        }
        return stack;
    }
}

fn main() {
    assert_eq!(Solution::asteroid_collision(vec![5, 10, -5]), vec![5, 10]);
    assert_eq!(Solution::asteroid_collision(vec![8, -8]), vec![]);
    assert_eq!(Solution::asteroid_collision(vec![10, 2, -5]), vec![10]);
    assert_eq!(Solution::asteroid_collision(vec![-2, -1, 1, 2]), vec![-2, -1, 1, 2]);
}