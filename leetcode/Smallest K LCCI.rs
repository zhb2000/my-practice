//Smallest K LCCI
//https://leetcode-cn.com/problems/smallest-k-lcci/
//快排（快速选择）
struct Solution;


impl Solution {
    pub fn smallest_k(mut arr: Vec<i32>, k: i32) -> Vec<i32> {
        Self::solve(&mut arr, k as usize);
        return arr[..(k as usize)].iter().cloned().collect();
    }

    fn solve(arr: &mut [i32], k: usize) {
        let n = arr.len();
        if n == 0 || n == 1 {
            return;
        }
        let pivot_pos = Self::partition(arr);
        let left_num = pivot_pos - 0;
        // let right_num = n - (pivot_pos + 1);
        if left_num + 1 == k {
            return;
        } else if k <= left_num {
            Self::solve(&mut arr[..pivot_pos], k);
        } else {
            assert!(k > left_num + 1);
            Self::solve(&mut arr[pivot_pos + 1..], k - (left_num + 1));
        }
    }

    //return the position of pivot
    fn partition(arr: &mut [i32]) -> usize {
        let n = arr.len();
        assert!(n > 0);
        if n == 1 {
            return 0;
        }
        let pivot = arr[n - 1];
        let mut l = 0;
        let mut r = n - 2;
        while l < r {
            while l < r && arr[l] < pivot {
                l += 1;
            }
            while l < r && arr[r] >= pivot {
                r -= 1;
            }
            let tmp = arr[l];
            arr[l] = arr[r];
            arr[r] = tmp;
        }
        let pivot_pos = if arr[l] < pivot { l + 1 } else { l };
        assert!(arr[pivot_pos] >= pivot);
        let tmp = arr[pivot_pos];
        arr[pivot_pos] = arr[n - 1];
        arr[n - 1] = tmp;
        return pivot_pos;
    }
}

fn main() {
    //[1, 2, 3, 4]
    println!("{:?}", Solution::smallest_k(vec![1, 3, 5, 7, 2, 4, 6, 8], 4));
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
