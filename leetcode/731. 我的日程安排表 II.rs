// 731. 我的日程安排表 II
// https://leetcode.cn/problems/my-calendar-ii/
// 有序容器、二分查找
use std::cmp::{max, min};
use std::collections::BTreeMap;

struct MyCalendarTwo {
    // start -> end
    map1: BTreeMap<i32, i32>,
    map2: BTreeMap<i32, i32>,
}

impl MyCalendarTwo {
    fn new() -> Self {
        Self { map1: BTreeMap::new(), map2: BTreeMap::new() }
    }

    fn book(&mut self, mut start: i32, mut end: i32) -> bool {
        if Self::get_overlap(&self.map2, start, end).is_some() {
            return false;
        }
        while let Some((s1, e1)) = Self::get_overlap(&self.map1, start, end) {
            let (si, ei) = Self::intersect(start, end, s1, e1);
            assert!(Self::get_overlap(&self.map2, si, ei).is_none());
            self.map2.insert(si, ei);
            let union = Self::union(start, end, s1, e1);
            start = union.0;
            end = union.1;
            self.map1.remove(&s1);
        }
        self.map1.insert(start, end);
        return true;
    }

    fn get_overlap(map: &BTreeMap<i32, i32>, start: i32, end: i32) -> Option<(i32, i32)> {
        match map.range(..end).last() {
            Some((&st, &ed)) if ed > start => Some((st, ed)),
            _ => None
        }
    }

    fn intersect(s1: i32, e1: i32, s2: i32, e2: i32) -> (i32, i32) {
        (max(s1, s2), min(e1, e2))
    }

    fn union(s1: i32, e1: i32, s2: i32, e2: i32) -> (i32, i32) {
        (min(s1, s2), max(e1, e2))
    }
}

fn main() {
    let mut c = MyCalendarTwo::new();
    assert!(c.book(10, 20));
    assert!(c.book(50, 60));
    assert!(c.book(10, 40));
    assert!(!c.book(5, 15));
    assert!(c.book(5, 10));
    assert!(c.book(25, 55));
}