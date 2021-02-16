//P3378 【模板】堆
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include <deque>
#include <map>
#include <variant>
#include <string_view>
#include <initializer_list>
#include <functional>
#include <memory>
#include <stack>
#include <deque>
#include <unordered_set>
#include <optional>

//using namespace std;

template <class T, class Comparator = std::less<T>>
class BiHeap
{
public:
	BiHeap(Comparator cmp = Comparator{})
		: data(1),
		  less_than(cmp) {}

	template <class Iter>
	BiHeap(Iter start, Iter stop, Comparator cmp = Comparator{})
		: data(1),
		  less_than(cmp)
	{
		for (Iter it = start; it != stop; ++it)
			data.push_back(*it);
		for (int i = fa(size()); i >= 1; i--)
			sift_down(i);
	}

	int size() { return int(data.size()) - 1; }

	bool empty() { return size() == 0; }

	void push(const T &elem)
	{
		data.push_back(elem);
		sift_up(size());
	}

	T &top() { return data[1]; }

	void pop() { delete_elem(1); }

private:
	std::vector<T> data;
	Comparator less_than;

	void sift_up(int i)
	{
		while (i != 1)
		{
			if (less_than(data[fa(i)], data[i]))
			{
				std::swap(data[i], data[fa(i)]);
				i = fa(i);
			}
			else
				break;
		}
	}

	void sift_down(int i)
	{
		while (lch(i) <= size()) // i is not a leaf
		{
			int bigger = lch(i);
			if (rch(i) <= size() && less_than(data[lch(i)], data[rch(i)]))
				bigger = rch(i);
			if (less_than(data[i], data[bigger]))
			{
				std::swap(data[i], data[bigger]);
				i = bigger;
			}
			else
				break;
		}
	}

	void delete_elem(int i)
	{
		std::swap(data[i], data[size()]);
		if (i == size()) // i is the last element
		{
			data.pop_back();
			return;
		}

		if (less_than(data[i], data[size()])) // replace < deleted
		{
			data.pop_back();
			sift_down(i);
		}
		else
		{
			data.pop_back();
			sift_up(i);
		}
	}

	static int fa(int i) { return i / 2; }
	static int lch(int i) { return i * 2; }
	static int rch(int i) { return i * 2 + 1; }
};

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	BiHeap<int, std::greater<int>> heap;
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		int op;
		std::cin >> op;
		if (op == 1)
		{
			int x;
			std::cin >> x;
			heap.push(x);
		}
		else if (op == 2)
			std::cout << heap.top() << "\n";
		else
			heap.pop();
	}

#ifdef CONSOLE_PAUSE
	system("PAUSE");
#endif
	return 0;
}