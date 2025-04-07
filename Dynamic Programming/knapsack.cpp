/*
  🧠 Problem: 0/1 Knapsack

  You're given:
  - N items, each with a weight and a value.
  - A knapsack that can carry a maximum weight of W.
  - You need to find the maximum total value that can be carried in the knapsack,
    without breaking any items (0/1 constraint).

  🔍 Approach: Dynamic Programming (Bottom-Up)

  1. Define dp[i][w] as the maximum value we can get using the first 'i' items and capacity 'w'.
  2. Initialize a dp table of size (N+1) x (W+1) with 0s.
     - Base Case: If no items or capacity is 0, max value = 0
  3. Transition:
     - If current item's weight ≤ w, we have two choices:
        a. Exclude the item → dp[i][w] = dp[i-1][w]
        b. Include the item → dp[i][w] = values[i-1] + dp[i-1][w - weights[i-1]]
        Take the maximum of these.
     - Else: item can't be included → dp[i][w] = dp[i-1][w]
  4. Final answer is dp[N][W]

  ⏱ Time Complexity: O(N * W)
  💾 Space Complexity: O(N * W)
*/

int knapsack(int N, int W, vector<int>& weights, vector<int>& values) {
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= N; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(
                    dp[i - 1][w], 
                    values[i - 1] + dp[i - 1][w - weights[i - 1]]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[N][W];
}
