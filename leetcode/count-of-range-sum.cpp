//区间和的个数
//https://leetcode-cn.com/classic/problems/count-of-range-sum/description/
//O(n(logn)^2) 做法，分治
using namespace std;
using ll = long long;

class Solution
{
public:
	int countRangeSum(vector<int> &nums, int lower, int upper)
	{
		vector<ll> ll_nums;
		for (int num : nums)
			ll_nums.push_back(num);
		return solve(0, int(nums.size()), ll_nums, lower, upper);
	}
	static int solve(int start, int stop, const vector<ll> &nums, int lower, int upper)
	{
		if (stop - start <= 5)
			return force(start, stop, nums, lower, upper);
		int mid = start + (stop - start) / 2;
		vector<ll> left_sums = get_left_sums(nums, start, mid);
		vector<ll> right_sums = get_right_sums(nums, mid, stop);
		sort(right_sums.begin(), right_sums.end());
		int center_cnt = 0;
		for (ll lsum : left_sums)
		{
			center_cnt += get_in(right_sums, lower - lsum, upper - lsum);
		}
		int left_cnt = solve(start, mid, nums, lower, upper);
		int right_cnt = solve(mid, stop, nums, lower, upper);
		return left_cnt + right_cnt + center_cnt;
	}

	//count num in [lower, upper]
	static int get_in(const vector<ll> &arr, ll lower, ll upper)
	{
		auto p1 = lower_bound(arr.begin(), arr.end(), lower);
		auto p2 = upper_bound(arr.begin(), arr.end(), upper);
		return p2 - p1;
	}

	//[start, mid)
	static vector<ll> get_left_sums(const vector<ll> &nums, int start, int mid)
	{
		vector<ll> ret;
		ll sum = nums[mid - 1];
		ret.push_back(sum);
		for (int i = mid - 2; i >= start; i--)
		{
			sum += nums[i];
			ret.push_back(sum);
		}
		return ret;
	}

	//[mid, stop)
	static vector<ll> get_right_sums(const vector<ll> &nums, int mid, int stop)
	{
		vector<ll> ret;
		ll sum = nums[mid];
		ret.push_back(sum);
		for (int i = mid + 1; i < stop; i++)
		{
			sum += nums[i];
			ret.push_back(sum);
		}
		return ret;
	}

	static int force(int start, int stop, const vector<ll> &nums, int lower, int upper)
	{
		int len = stop - start;
		ll arr[10];
		ll pre_sum[10];
		for (int i = 1; i <= len; i++)
			arr[i] = nums[start + i - 1];
		pre_sum[0] = 0;
		for (int i = 1; i <= len; i++)
			pre_sum[i] = pre_sum[i - 1] + arr[i];
		int cnt = 0;
		//[i, j]
		for (int i = 1; i <= len; i++)
		{
			for (int j = i; j <= len; j++)
			{
				ll temp = pre_sum[j] - pre_sum[i - 1];
				if (lower <= temp && temp <= upper)
					cnt += 1;
			}
		}
		return cnt;
	}
};