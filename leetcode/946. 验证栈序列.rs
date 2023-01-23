// 946. 验证栈序列
// https://leetcode.cn/problems/validate-stack-sequences/
// 栈、思维题
// 若栈顶与 popped 当前值相同，则出栈，否则从 pushed 取一个元素入栈
struct Solution;

impl Solution {
    pub fn validate_stack_sequences(pushed: Vec<i32>, popped: Vec<i32>) -> bool {
        let mut pushed = pushed.iter().peekable();
        let mut popped = popped.iter().peekable();
        let mut stack: Vec<&i32> = vec![];
        while pushed.peek().is_some() || popped.peek().is_some() {
            if stack.last() == popped.peek() {
                stack.pop();
                popped.next();
            } else if let Some(x) = pushed.next() {
                stack.push(x);
            } else {
                return false;
            }
        }
        return true;
    }
}

fn main() {
    assert!(Solution::validate_stack_sequences(
        vec![1, 2, 3, 4, 5],
        vec![4, 5, 3, 2, 1]
    ));
    assert!(!Solution::validate_stack_sequences(
        vec![1, 2, 3, 4, 5],
        vec![4, 3, 5, 1, 2]
    ));
}
