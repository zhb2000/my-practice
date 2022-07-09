// 1642. 可以到达的最远建筑
// https://leetcode.cn/problems/furthest-building-you-can-reach
// 用小根堆来维护 Top-K
struct Solution;

use std::cmp::Reverse;
use std::collections::BinaryHeap;

impl Solution {
    pub fn furthest_building(heights: Vec<i32>, bricks: i32, ladders: i32) -> i32 {
        let mut topk = BinaryHeap::new();
        let mut rest_sum = 0;
        let mut ans = 0;
        for i in 1..heights.len() {
            let h = heights[i] - heights[i - 1];
            if h <= 0 {
                ans = i as i32;
                continue;
            }
            topk.push(Reverse(h));
            if topk.len() as i32 > ladders {
                rest_sum += topk.pop().unwrap().0;
            }
            if rest_sum > bricks {
                break;
            } else {
                ans = i as i32;
            }
        }
        return ans;
    }
}

fn main() {
    assert_eq!(Solution::furthest_building(vec![4, 2, 7, 6, 9, 14, 12], 5, 1), 4);
    assert_eq!(Solution::furthest_building(vec![4, 12, 2, 7, 3, 18, 20, 3, 19], 10, 2), 7);
    assert_eq!(Solution::furthest_building(vec![14, 3, 19, 3], 17, 10), 3);
}