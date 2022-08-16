// 1206. 设计跳表
// https://leetcode.cn/problems/design-skiplist/
// 单链表 + 随机层数实现
// Vec + 下标做为内存池
use std::ops::{Index, IndexMut};
use rand::Rng;

const MAX_LEVEL: usize = 8;

struct Node {
    value: i32,
    height: usize,
    next: [Option<usize>; MAX_LEVEL],
}

impl Node {
    fn new(value: i32, height: usize) -> Self {
        Self { value, height, next: [None; MAX_LEVEL] }
    }
}

struct Skiplist {
    head: usize,
    pool: Pool<Node>,
}

impl Skiplist {
    fn new() -> Self {
        let mut pool = Pool::with_capacity(5e4 as usize + 5);
        return Self { head: pool.alloc(Node::new(-1, MAX_LEVEL)), pool };
    }

    fn find_geq(&self, value: i32) -> (Option<usize>, [usize; MAX_LEVEL]) {
        let mut previous = [0; MAX_LEVEL];
        let mut p = self.head;
        for level in (0..MAX_LEVEL).rev() {
            while let Some(next) = self.pool[p].next[level]
                .filter(|&next| self.pool[next].value < value) {
                p = next;
            }
            previous[level] = p;
        }
        return (self.pool[p].next[0], previous);
    }

    fn search(&self, value: i32) -> bool {
        let (node, _) = self.find_geq(value);
        return node.filter(|&u| self.pool[u].value == value).is_some();
    }

    fn random_height() -> usize {
        let mut height = 1;
        while height < MAX_LEVEL && rand::thread_rng().gen::<u32>() % 4 == 0 {
            height += 1;
        }
        return height;
    }

    fn add(&mut self, value: i32) {
        let height = Self::random_height();
        let node = self.pool.alloc(Node::new(value, height));
        let (_, previous) = self.find_geq(value);
        for level in 0..height {
            let prev = previous[level];
            self.pool[node].next[level] = self.pool[prev].next[level];
            self.pool[prev].next[level] = Some(node);
        }
    }

    fn erase(&mut self, value: i32) -> bool {
        let (node, previous) = self.find_geq(value);
        return match node {
            Some(node) if self.pool[node].value == value => {
                for level in 0..self.pool[node].height {
                    let prev = previous[level];
                    self.pool[prev].next[level] = self.pool[node].next[level];
                }
                self.pool.free(node);
                true
            }
            _ => false
        };
    }
}

struct Pool<T> {
    data: Vec<T>,
    indices: Vec<usize>,
}

impl<T> Pool<T> {
    fn with_capacity(capacity: usize) -> Self {
        Self {
            data: Vec::with_capacity(capacity),
            indices: Vec::with_capacity(capacity),
        }
    }

    fn alloc(&mut self, value: T) -> usize {
        return if let Some(index) = self.indices.pop() {
            self.data[index] = value;
            index
        } else {
            self.data.push(value);
            self.data.len() - 1
        };
    }

    fn free(&mut self, index: usize) { self.indices.push(index); }
}

impl<T> Index<usize> for Pool<T> {
    type Output = T;
    fn index(&self, index: usize) -> &Self::Output { self.data.index(index) }
}

impl<T> IndexMut<usize> for Pool<T> {
    fn index_mut(&mut self, index: usize) -> &mut Self::Output { self.data.index_mut(index) }
}

fn main() {
    let mut skiplist = Skiplist::new();
    skiplist.add(1);
    skiplist.add(2);
    skiplist.add(3);
    assert!(!skiplist.search(0));
    skiplist.add(4);
    assert!(skiplist.search(1));
    assert!(!skiplist.erase(0));
    assert!(skiplist.erase(1));
    assert!(!skiplist.search(1));
}
