//Number of Longest Increasing Subsequence
//https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/
//二分查找 + DP，时间复杂度 O(n^2)
struct Solution;

#[derive(Copy, Clone)]
struct Entry {
    value: i32,
    num: i32,
}

impl Solution {
    pub fn find_number_of_lis(nums: Vec<i32>) -> i32 {
        let n = nums.len();
        if n == 0 {
            return 0;
        }
        let mut d: Vec<Vec<Entry>> = vec![vec![]; n];
        d[0].push(Entry { value: nums[0], num: 1 });
        let mut len = 1;
        for &value in nums[1..].iter() {
            let index = Self::lower_bound(&d[..len], value);
            let num = if index >= 1 { Self::less_value_num(&d[index - 1], value) } else { 1 };
            if index == len {
                d[index].push(Entry { value, num });
                len += 1;
            } else {
                assert!(value <= d[index].last().unwrap().value);
                if value < d[index].last().unwrap().value {
                    d[index].push(Entry { value, num });
                } else { // equals
                    d[index].last_mut().unwrap().num += num;
                }
            }
        }
        return d[len - 1].iter().map(|e| e.num).sum();
    }

    fn less_value_num(v: &Vec<Entry>, value: i32) -> i32 {
        let mut num = 0;
        for e in v.iter().rev() {
            if e.value >= value {
                break;
            }
            num += e.num;
        }
        return num;
    }

    fn lower_bound(elements: &[Vec<Entry>], value: i32) -> usize {
        let mut l = 0;
        let mut r = elements.len();
        while l < r {
            let m = l + ((r - l) >> 1);
            if elements[m].last().unwrap().value >= value {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }
}

fn main() {
    assert_eq!(Solution::find_number_of_lis(vec![1, 3, 5, 4, 7]), 2);
    assert_eq!(Solution::find_number_of_lis(vec![2, 2, 2, 2, 2]), 5);
    assert_eq!(Solution::find_number_of_lis(vec![2]), 1);
    assert_eq!(Solution::find_number_of_lis(vec![]), 0);
    assert_eq!(Solution::find_number_of_lis(vec![1, 2, 4, 3, 5, 4, 7, 2]), 3);
    //1 2 4 5 7; 1 2 3 5 7; 1 2 3 4 7
    assert_eq!(Solution::find_number_of_lis(vec![1, 1, 1, 2, 2, 2, 3, 3, 3]), 27);
    assert_eq!(Solution::find_number_of_lis(vec![2, 1]), 2);
}


#[allow(dead_code)]
fn lower_bound<T: PartialOrd>(elements: &[T], value: &T) -> usize {
    let mut l = 0;
    let mut r = elements.len();
    while l < r {
        let m = l + ((r - l) >> 1);
        if elements[m] >= *value {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

#[allow(dead_code)]
fn upper_bound<T: PartialOrd>(elements: &[T], value: &T) -> usize {
    let mut l = 0;
    let mut r = elements.len();
    while l < r {
        let m = l + ((r - l) >> 1);
        if elements[m] <= *value {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}
