//Design Add and Search Words Data Structure
//https://leetcode-cn.com/problems/design-add-and-search-words-data-structure/
//字典树
use std::collections::HashMap;

struct Node {
    ch: char,
    children: HashMap<char, Box<Node>>,
    accepted: bool,
}

impl Node {
    fn new(ch: char) -> Self {
        Node { ch, children: HashMap::new(), accepted: false }
    }

    fn add_rest(&mut self, rest_word: &[char]) {
        if rest_word.is_empty() { //no next char
            self.accepted = true;
            return;
        }
        let ch = rest_word[0];//next char
        if !self.children.contains_key(&ch) {
            self.children.insert(ch, Box::new(Node::new(ch)));
        }
        let node = self.children.get_mut(&ch).unwrap();//next node
        node.add_rest(&rest_word[1..]);
    }

    fn find_rest(&self, rest_word: &[char]) -> bool {
        assert!(!rest_word.is_empty());
        let ch = rest_word[0];
        if rest_word.len() == 1 {
            return (ch == '.' || ch == self.ch) && self.accepted;//last char
        }
        if ch != '.' && ch != self.ch {
            return false;//char not match
        }
        return self.children
            .values()
            .any(|node| node.find_rest(&rest_word[1..]));
    }
}

struct WordDictionary {
    root: Node,
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl WordDictionary {
    fn new() -> Self {
        WordDictionary { root: Node::new('\0') }
    }

    fn add_word(&mut self, word: String) {
        let word: Vec<char> = word.chars().collect();
        self.root.add_rest(&word);
    }

    fn search(&self, word: String) -> bool {
        let word: Vec<char> = word.chars().collect();
        if word.is_empty() {
            return true;
        }
        return self.root.children
            .values()
            .any(|node| node.find_rest(&word));
    }
}

/**
 * Your WordDictionary object will be instantiated and called as such:
 * let obj = WordDictionary::new();
 * obj.add_word(word);
 * let ret_2: bool = obj.search(word);
 */

fn main() {
    let mut w = WordDictionary::new();
    w.add_word("bad".to_string());
    w.add_word("dad".to_string());
    w.add_word("mad".to_string());
    assert_eq!(w.search("pad".to_string()), false); // return False
    assert_eq!(w.search("bad".to_string()), true); // return True
    assert_eq!(w.search(".ad".to_string()), true); // return True
    assert_eq!(w.search("b..".to_string()), true); // return True
}
