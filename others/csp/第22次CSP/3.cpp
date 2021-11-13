#ifndef LOCAL
#define NDEBUG
#endif // close assert if not local
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<functional>
#include<algorithm>
#include<vector>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<stack>
#include<queue>
#include<deque>
#include<utility>
#include<tuple>
#include<bitset>
#include<cassert>
#include<cctype>
#include<cmath>
#include<numeric>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int, int> Pii;
template <class Int>
inline Int fast_read()
{
	Int x = 0, f = 1; char ch = char(getchar());
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = char(getchar()); }
	while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = char(getchar()); }
	return x * f;
}
inline int readint() { return fast_read<int>(); }
inline ll readll() { return fast_read<ll>(); }
inline void cpp_io() { ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); }
template <class T>
ostream &operator<<(ostream &os, const vector<T> &vec)
{
	os << "["; bool isfirst = true;
	for (const auto &x : vec)
	{
		if (isfirst) isfirst = false;
		else os << ", ";
		os << x;
	}
	os << "]"; return os;
}
template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p)
{
	os << "(" << p.first << ", " << p.second << ")"; return os;
}
template <class Int>
inline Int avg2(Int a, Int b) { assert(a <= b); return a + ((b - a) >> 1); }
template <class Int>
inline Int clen(Int l, Int r) { assert(l - 1 <= r); return r - l + 1; }
template <class Int>
inline bool isodd(Int num) { return (num & 1) != 0; }
template <class Int>
inline bool iseven(Int num) { return (num & 1) == 0; }
const int INTMAX = ~(1 << 31);
const double EPS = 1e-6;
//------------------------ header end ------------------------

enum MsgType { DIS, OFR, REQ, ACK, NAK };
string to_string(MsgType type)
{
	if (type == DIS) return "DIS";
	else if (type == OFR) return "OFR";
	else if (type == REQ) return "REQ";
	else if (type == ACK) return "ACK";
	else { assert(type == NAK); return "NAK"; }
}
MsgType str2type(const string &type)
{
	if (type == "DIS") return DIS;
	else if (type == "OFR") return OFR;
	else if (type == "REQ") return REQ;
	else if (type == "ACK") return ACK;
	else { assert(type == "NAK"); return NAK; }
}


struct Message
{
	string send;
	string recv;
	MsgType type;
	int ip;
	int expire;
};
string to_string(const Message &m)
{
	return string().append(m.send).append(" ")
		.append(m.recv).append(" ")
		.append(to_string(m.type)).append(" ")
		.append(to_string(m.ip)).append(" ")
		.append(to_string(m.expire));
}

enum AddrStat { Free, Wait, Owned, Expired };
struct Address
{
	int ip;
	AddrStat status = Free;
	string owner;
	int expire = 0;
};

struct Server
{
	int n; int t_def; int t_max; int t_min; string host;
	vector<Address> pool;
	int current_tick = 0;
	//status index
	set<int> free_set;
	set<int> expired_set;
	//owner index
	unordered_map<string, int> owner2ip;
	//expire index
	map<int, set<int>> expire2ips;

	Server(int n, int t_def, int t_max, int t_min, string host)
		:n(n), t_def(t_def), t_max(t_max), t_min(t_min), host(host)
	{
		init_pool(n);
	}

	void init_pool(int n)
	{
		pool.reserve(n + 1);
		for (int i = 0; i <= n + 1; i++)
			pool.push_back(Address{});
		for (int ip = 1; ip <= n; ip++)
			free_set.insert(ip);
	}

	//return -1 if none
	int min_free() const
	{
		for (int ip : free_set)
		{
			assert(pool[ip].status == Free);
			return ip;
		}
		return -1;
	}

	//return -1 if none
	int min_expired() const
	{
		for (int ip : expired_set)
		{
			assert(pool[ip].status == Expired);
			return ip;
		}
		return -1;
	}

	//return -1 if none
	int select_ip(const string &sender) const
	{
		int ip = -1;
		if (owner2ip.count(sender))
		{
			ip = owner2ip.at(sender);
			return ip;
		}
		ip = min_free();
		if (ip != -1)
			return ip;
		ip = min_expired();
		if (ip != -1)
			return ip;
		return -1;
	}

	//- set owner to empty
	//- modify owner2ip
	void clear_onceowner(int ip)
	{
		const string &old_owner = pool[ip].owner;
		if (old_owner.empty())
			return;
		assert(owner2ip.count(old_owner));
		owner2ip.erase(old_owner);
		pool[ip].owner.clear();
	}

	//- set owner
	//- modify owner2ip
	void set_owner(int ip, const string &new_owner)
	{
		clear_onceowner(ip);
		pool[ip].owner = new_owner;
		owner2ip[new_owner] = ip;
	}

	//- set expire to zero
	//- modify expire2ips
	void clear_expire(int ip)
	{
		int old_expire = pool[ip].expire;
		if (old_expire == 0)
			return;
		assert(expire2ips.count(old_expire));
		assert(expire2ips[old_expire].count(ip));
		expire2ips[old_expire].erase(ip);
		if (expire2ips[old_expire].empty())
			expire2ips.erase(old_expire);
		pool[ip].expire = 0;
	}

	//- set expire
	//- modify expire2ips
	void set_expire(int ip, int new_expire)
	{
		clear_expire(ip);
		pool[ip].expire = new_expire;
		if (!expire2ips.count(new_expire))
			expire2ips[new_expire] = {};
		expire2ips[new_expire].insert(ip);
	}

	//- set status
	//- modify free_set, expired_set
	void set_status(int ip, AddrStat new_stat)
	{
		AddrStat old_stat = pool[ip].status;
		if (old_stat == Free)
			free_set.erase(ip);
		else if (old_stat == Expired)
			expired_set.erase(ip);
		pool[ip].status = new_stat;
		if (new_stat == Free)
			free_set.insert(ip);
		else if (new_stat == Expired)
			expired_set.insert(ip);
	}

	void update_tick(int current_tick)
	{
		this->current_tick = current_tick;
		vector<int> ips; // expired ips
		for (const auto &kv : expire2ips)
		{
			int expire = kv.first;
			const auto &s = kv.second;
			if (expire <= current_tick)
				ips.insert(ips.end(), s.begin(), s.end());
			else
				break;
		}
		for (int ip : ips)
		{
			clear_expire(ip);
			assert(pool[ip].status == Wait || pool[ip].status == Owned);
			if (pool[ip].status == Wait)
			{
				set_status(ip, Free);//wait to free, clear owner
				clear_onceowner(ip);
			}
			else // Owned
				set_status(ip, Expired);
		}
	}

	void handle_discover(const Message &m)
	{
		int ip = select_ip(m.send);
		if (ip == -1)
			return;
		set_status(ip, Wait);
		set_owner(ip, m.send);
		int expire = calc_expire(m.expire);
		set_expire(ip, expire);
		auto msg = Message{ host, m.send, OFR, ip, expire };
		cout << to_string(msg) << "\n";
	}

	void handle_request(const Message &m)
	{
		if (m.recv != host && m.recv != "*")
		{
			if (owner2ip.count(m.send))
			{
				int ip = owner2ip[m.send];
				if (pool[ip].status == Wait)
				{
					set_status(ip, Free);//wait to free, clear owner
					clear_onceowner(ip);
					clear_expire(ip);
				}
			}
		}
		else if (m.ip <= n && pool[m.ip].owner == m.send)
		{
			set_status(m.ip, Owned);
			int expire = calc_expire(m.expire);
			set_expire(m.ip, expire);
			auto msg = Message{ host, m.send, ACK, m.ip, expire };
			cout << to_string(msg) << "\n";
		}
		else
		{
			auto msg = Message{ host, m.send, NAK, m.ip, 0 };//nak, ip and expire?
			cout << to_string(msg) << "\n";
		}
	}

	void handle_message(const Message &m)
	{
		if (m.type != DIS && m.type != REQ)
			return;
		if (m.type == DIS && m.recv == "*")
			handle_discover(m);
		else if (m.type == REQ && m.recv != "*")
		{
			//recv is host or other
			handle_request(m);
		}
	}

	int calc_expire(int want_expire) const
	{
		if (want_expire == 0)
			return current_tick + t_def;
		int len = want_expire - current_tick;
		if (len < t_min)
			len = t_min;
		else if (len > t_max)
			len = t_max;
		return current_tick + len;
	}
};

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
#endif

	cpp_io();

	int pool_n, t_def, t_max, t_min; string host;
	cin >> pool_n >> t_def >> t_max >> t_min >> host;
	auto server = Server(pool_n, t_def, t_max, t_min, host);

	int msg_num;
	cin >> msg_num;
	int tick; string send, recv, type; int ip, expire;
	for (int c = 1; c <= msg_num; c++)
	{
		cin >> tick >> send >> recv >> type >> ip >> expire;
		auto msg = Message{ send, recv, str2type(type), ip, expire };
		server.update_tick(tick);
		server.handle_message(msg);
	}


#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}
