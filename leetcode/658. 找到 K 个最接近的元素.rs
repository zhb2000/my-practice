// 658. 找到 K 个最接近的元素
// https://leetcode.cn/problems/find-k-closest-elements/
// 二分查找
struct Solution;

impl Solution {
    pub fn find_closest_elements(arr: Vec<i32>, k: i32, x: i32) -> Vec<i32> {
        let mut j = arr.partition_point(|&num| num < x); // lower bound of x
        let mut i = (j as isize - 1) as usize;
        let mut result = vec![];
        while result.len() < k as usize {
            match (arr.get(i), arr.get(j)) {
                (Some(&a), None) => {
                    result.push(a);
                    i = (i as isize - 1) as usize;
                }
                (None, Some(&b)) => {
                    result.push(b);
                    j += 1;
                }
                (Some(&a), Some(&b)) => {
                    if (a - x).abs() <= (b - x).abs() {
                        result.push(a);
                        i = (i as isize - 1) as usize;
                    } else {
                        result.push(b);
                        j += 1;
                    }
                }
                (None, None) => panic!()
            }
        }
        result.sort();
        return result;
    }
}

fn main() {
    assert_eq!(Solution::find_closest_elements(vec![1, 2, 3, 4, 5], 4, 3), vec![1, 2, 3, 4]);
    assert_eq!(Solution::find_closest_elements(vec![1, 2, 3, 4, 5], 4, -1), vec![1, 2, 3, 4]);
}
