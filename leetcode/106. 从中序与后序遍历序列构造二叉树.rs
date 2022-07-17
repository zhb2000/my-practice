// 106. 从中序与后序遍历序列构造二叉树
// https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
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
    pub fn build_tree(inorder: Vec<i32>, postorder: Vec<i32>) -> Option<Rc<RefCell<TreeNode>>> {
        return Self::build(&inorder, &postorder);
    }

    fn build(inorder: &[i32], postorder: &[i32]) -> Option<Rc<RefCell<TreeNode>>> {
        if inorder.is_empty() {
            return None;
        }
        let val = postorder[postorder.len() - 1];
        let i = inorder.iter().position(|&x| x == val).unwrap();
        let left = Self::build(&inorder[..i], &postorder[..i]);
        let right = Self::build(&inorder[i + 1..], &postorder[i..postorder.len() - 1]);
        return Some(Rc::new(RefCell::new(TreeNode { val, left, right })));
    }
}


fn main() {}