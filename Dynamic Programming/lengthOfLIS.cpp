/*
  Problem:
  Given an integer array nums, return the length of the longest strictly increasing subsequence.

  Approaches:
  -------------------------
  1. Dynamic Programming (O(n^2)):
     - For each element nums[i], we look back at all previous elements nums[j] (j < i),
       and if nums[j] < nums[i], we try to extend the LIS ending at j.
     - dp[i] stores the length of LIS ending at index i.
     - Final answer is the max value in dp[].

  2. Binary Search + Greedy (O(n log n)):
     - Maintain a `tails[]` array where tails[i] stores the minimum ending number
       of an increasing subsequence of length i+1.
     - For each number:
         - If it can extend the current longest sequence (num > tails.back()), push it.
         - Else, replace the first number in tails[] that is >= num using lower_bound.
     - The size of tails[] at the end is the length of LIS.
*/

#include <vector>
#include <algorithm>  // for std::max and std::lower_bound
using namespace std;

class Solution {
 public:
  // Brute Force DP Approach - O(n^2)
  int lengthOfLIS_DP(const vector<int>& nums) {
    if (nums.empty()) return 0;

    vector<int> dp(nums.size(), 1);  // dp[i]: LIS ending at index i

    for (int i = 1; i < nums.size(); ++i)
      for (int j = 0; j < i; ++j)
        if (nums[j] < nums[i])
          dp[i] = max(dp[i], dp[j] + 1);

    return *max_element(dp.begin(), dp.end());
  }

  // Optimized Approach using Binary Search - O(n log n)
  int lengthOfLIS(const vector<int>& nums) {
    // tails[i]: the minimum tail value of an increasing subsequence of length i+1
    vector<int> tails;

    for (int num : nums) {
      if (tails.empty() || num > tails.back()) {
        // Case 1: num extends the largest subsequence
        tails.push_back(num);
      } else {
        // Case 2: Replace the first element in tails >= num
        int idx = firstGreaterEqual(tails, num);
        tails[idx] = num;
      }
    }

    return tails.size();
  }

 private:
  // Helper to find first index where value >= target using binary search
  int firstGreaterEqual(const vector<int>& arr, int target) {
    return lower_bound(arr.begin(), arr.end(), target) - arr.begin();
  }
};
