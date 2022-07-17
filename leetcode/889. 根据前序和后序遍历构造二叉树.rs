// 889. 根据前序和后序遍历构造二叉树
// https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-postorder-traversal/
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

struct Solution;

use std::rc::Rc;
use std::cell::RefCell;

impl Solution {
    pub fn construct_from_pre_post(preorder: Vec<i32>, postorder: Vec<i32>) -> Option<Rc<RefCell<TreeNode>>> {
        return Self::build(&preorder, &postorder);
    }

    fn build(preorder: &[i32], postorder: &[i32]) -> Option<Rc<RefCell<TreeNode>>> {
        if preorder.is_empty() {
            return None;
        }
        if preorder.len() == 1 {
            return Some(Rc::new(RefCell::new(TreeNode { val: preorder[0], left: None, right: None })));
        }
        let l = postorder.iter().position(|&x| x == preorder[1]).unwrap() + 1;
        let left = Self::build(&preorder[1..1 + l], &postorder[..l]);
        let right = Self::build(&preorder[1 + l..], &postorder[l..postorder.len() - 1]);
        return Some(Rc::new(RefCell::new(TreeNode { val: preorder[0], left, right })));
    }
}

fn main() {}