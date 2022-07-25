// 729. 我的日程安排表 I
// https://leetcode.cn/problems/my-calendar-i/
// 有序容器、二分查找
use std::collections::BTreeMap;

struct MyCalendar {
    map: BTreeMap<i32, i32>, // start -> end
}

impl MyCalendar {
    fn new() -> Self {
        MyCalendar { map: BTreeMap::new() }
    }

    fn book(&mut self, start: i32, end: i32) -> bool {
        let available = match self.map.range(..end).last() {
            Some((_, &ed)) if ed > start => false,
            _ => true
        };
        if available {
            self.map.insert(start, end);
        }
        return available;
    }
}

fn main() {
    let mut c = MyCalendar::new();
    // assert!(c.book(10, 20));
    // assert!(!c.book(15, 25));
    // assert!(c.book(20, 30));

    assert!(c.book(25, 32));
    assert!(c.book(19, 25));
    assert!(c.book(3, 8));
    assert!(!c.book(18, 27));
}