// 105. 从前序与中序遍历序列构造二叉树
// https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
// 根据前序找根节点，在根据中序找左右子树
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
    pub fn build_tree(preorder: Vec<i32>, inorder: Vec<i32>) -> Option<Rc<RefCell<TreeNode>>> {
        return Self::build(&preorder, &inorder);
    }

    fn build(preorder: &[i32], inorder: &[i32]) -> Option<Rc<RefCell<TreeNode>>> {
        if preorder.is_empty() {
            return None;
        }
        let val = preorder[0];
        let i = inorder.iter().position(|&x| x == val).unwrap();
        let left = Self::build(&preorder[1..1 + i], &inorder[..i]);
        let right = Self::build(&preorder[1 + i..], &inorder[i + 1..]);
        return Some(Rc::new(RefCell::new(TreeNode { val, left, right })));
    }
}


fn main() {}