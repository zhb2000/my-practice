# 最大子序和（DP）
# https://leetcode-cn.com/classic/problems/maximum-subarray/description/
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        n = len(nums)
        dp = [0 for _ in range(n)]
        dp[0] = nums[0]
        for i in range(1, n):
            dp[i] = max(dp[i - 1] + nums[i], nums[i])
        ans = dp[0]
        for i in range(1, n):
            ans = max(ans, dp[i])
        return ans
