/*
  🧠 Problem: Maximum Sum Increasing Subsequence

  You're given an array of positive integers. You need to find the **maximum possible sum**
  of a subsequence such that the subsequence is **strictly increasing**.

  🔍 Approach: Dynamic Programming

  1. Let `dp[i]` represent the maximum sum of an increasing subsequence ending at index `i`.

  2. Initialize dp[i] = arr[i] for all i
     → Because the minimum sum we can take ending at index i is the value of arr[i] itself.

  3. Traverse each index `i` from 1 to n-1:
     - For each `j` from 0 to i-1:
       - If arr[j] < arr[i], it means we can extend the subsequence ending at j to i.
       - Update dp[i] = max(dp[i], dp[j] + arr[i])

  4. After filling the dp array, the answer will be the maximum value in dp[].

  ✅ Final Answer = max(dp[0], dp[1], ..., dp[n-1])

  ⏱ Time Complexity: O(n^2)
  💾 Space Complexity: O(n)
*/

int maxSumIncreasingSubsequence(vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n);

    // Initialize: max sum ending at each index is at least the element itself
    for (int i = 0; i < n; ++i)
        dp[i] = arr[i];

    // Build the dp array using the logic of increasing subsequences
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (arr[j] < arr[i]) {
                dp[i] = max(dp[i], dp[j] + arr[i]);
            }
        }
    }

    // Return the maximum value from dp[] as the result
    return *max_element(dp.begin(), dp.end());
}
