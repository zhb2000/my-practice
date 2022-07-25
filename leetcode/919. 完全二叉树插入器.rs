// 919. 完全二叉树插入器
// https://leetcode.cn/problems/complete-binary-tree-inserter/
// 完全二叉树、堆式存储、BFS
use std::borrow::Borrow;
use std::cell::RefCell;
use std::collections::vec_deque::VecDeque;
use std::rc::Rc;

// Definition for a binary tree node.
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

struct CBTInserter {
    root: Option<Rc<RefCell<TreeNode>>>,
    v: Vec<Option<Rc<RefCell<TreeNode>>>>,
}

impl CBTInserter {
    fn new(root: Option<Rc<RefCell<TreeNode>>>) -> Self {
        let mut v = vec![None];
        if let Some(root) = root.clone() {
            let mut q = VecDeque::new();
            q.push_back(root);
            while let Some(u) = q.pop_front() {
                v.push(Some(u.clone()));
                if let Some(lch) = u.as_ref().borrow().left.clone() {
                    q.push_back(lch);
                }
                if let Some(rch) = u.as_ref().borrow().right.clone() {
                    q.push_back(rch);
                }
            }
        }
        Self { root, v }
    }

    fn insert(&mut self, val: i32) -> i32 {
        let index = self.v.len();
        let parent = self.v[index / 2].clone().unwrap();
        let node = Rc::new(RefCell::new(TreeNode::new(val)));
        if index % 2 == 0 {
            parent.borrow_mut().left = Some(node.clone());
        } else {
            parent.borrow_mut().right = Some(node.clone());
        }
        self.v.push(Some(node));
        return parent.as_ref().borrow().val;
    }

    fn get_root(&self) -> Option<Rc<RefCell<TreeNode>>> {
        self.root.clone()
    }
}


fn main() {}
