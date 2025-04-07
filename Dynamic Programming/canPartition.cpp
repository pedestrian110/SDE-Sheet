/*
  Problem: Partition Equal Subset Sum

  You're given an array of positive integers.
  Your task is to determine if it can be partitioned into two subsets such that the sum of elements in both subsets is equal.

  ✅ Approaches Used:
  -------------------
  1. 2D Dynamic Programming (DP) Table
  2. Space-Optimized 1D DP Array

  -------------------------------------------
  General Idea:
  - If total sum is odd, it's impossible to partition equally.
  - If sum is even, check if there's a subset with sum = total_sum / 2.
  - This becomes a classic 0/1 Knapsack problem where we try to pick elements that sum to a target.
  -------------------------------------------

  2D DP Approach:
  - Use a dp[n+1][target+1] table where dp[i][j] is true if a subset of the first i elements has sum j.
  - Transition: dp[i][j] = dp[i-1][j] || dp[i-1][j - nums[i-1]] if j >= nums[i-1]

  1D DP (Space-Optimized):
  - Compress 2D dp to 1D array since only previous row is needed.
  - Update dp[j] from right to left to avoid overwriting values used in current iteration.
*/

class Solution {
 public:
  bool canPartition(vector<int>& nums) {
    const int sum = accumulate(nums.begin(), nums.end(), 0);

    // If sum is odd, it's not possible to divide into two equal subsets
    if (sum % 2 == 1)
      return false;

    // Uncomment either approach below:

    // ------- 2D DP Table Approach -------
    // return knapsack2D(nums, sum / 2);

    // ------- 1D Space-Optimized DP -------
    return knapsack1D(nums, sum / 2);
  }

 private:
  // 2D DP Knapsack: dp[i][j] = true if a subset of first i elements sums to j
  bool knapsack2D(const vector<int>& nums, int target) {
    const int n = nums.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= n; ++i) {
      int num = nums[i - 1];
      for (int j = 0; j <= target; ++j) {
        if (j < num)
          dp[i][j] = dp[i - 1][j];  // Can't take current number
        else
          dp[i][j] = dp[i - 1][j] || dp[i - 1][j - num];  // Include or exclude
      }
    }

    return dp[n][target];
  }

  // 1D DP Optimized: dp[j] = true if sum j is achievable using any subset
  bool knapsack1D(const vector<int>& nums, int target) {
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int num : nums) {
      // Go backwards to ensure we don't reuse the same element
      for (int j = target; j >= num; --j) {
        dp[j] = dp[j] || dp[j - num];
      }
    }

    return dp[target];
  }
};
