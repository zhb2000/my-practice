// 535. TinyURL 的加密与解密
// https://leetcode.cn/problems/encode-and-decode-tinyurl/
// 设计题，自增 ID
use std::collections::HashMap;

struct Codec {
    map: HashMap<i32, String>,
}

impl Codec {
    fn new() -> Self {
        Self { map: HashMap::new() }
    }

    // Encodes a URL to a shortened URL.
    fn encode(&mut self, long_url: String) -> String {
        let (prefix, postfix) = Self::split_url(&long_url);
        let id = self.map.len() as i32;
        self.map.insert(id, postfix);
        return format!("{prefix}/{id}");
    }

    // Decodes a shortened URL to its original URL.
    fn decode(&self, short_url: String) -> String {
        let (prefix, id) = Self::split_url(&short_url);
        let postfix = self.map.get(&id.parse().unwrap()).unwrap();
        return format!("{prefix}/{postfix}");
    }

    fn split_url(url: &str) -> (String, String) {
        let split: Vec<&str> = url.split('/').collect();
        let prefix = split[..split.len() - 1].join("/");
        let postfix = split.last().unwrap().to_string();
        return (prefix, postfix);
    }
}

fn main() {
    let mut obj = Codec::new();
    let long = "https://leetcode.com/problems/design-tinyurl";
    let short = obj.encode(long.to_string());
    let long2 = obj.decode(short.clone());
    println!("short: {short}");
    println!("long2: {long2}");
}