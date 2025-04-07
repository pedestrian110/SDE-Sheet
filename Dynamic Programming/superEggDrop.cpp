/*
  Problem: Egg Dropping Puzzle

  You're given `n` eggs and a building with `k` floors.
  You must determine the highest floor `f` from which an egg can be dropped without breaking,
  using the **minimum number of moves in the worst case**.

  Rules:
  - You can reuse unbroken eggs.
  - Broken eggs are discarded.
  - All eggs behave identically.
  - An egg that breaks at floor x will break at any floor > x.
  - An egg that survives floor x will survive all floors < x.

  ✅ Approach: DP + Binary Search Optimization
  - Let `dp[n][k]` represent the minimum number of moves required using `n` eggs and `k` floors.
  - For each state, try dropping the egg from floor `x`:
      - If the egg breaks → reduce to `dp[n-1][x-1]`
      - If the egg doesn't break → reduce to `dp[n][k-x]`
      - Take the worst of both cases, since we must handle the worst case
  - Use binary search on `x` to minimize the number of moves efficiently (since dp[n][x] is convex).

  Time Complexity: O(n * k * log k) due to binary search in the inner loop
*/

class Solution {
 public:
  int superEggDrop(int n, int k) {
    // dp[i][j] = minimum number of moves with i eggs and j floors
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

    // Fill base cases:
    // With 1 egg, we need j moves for j floors (check one by one)
    for (int j = 1; j <= k; ++j)
      dp[1][j] = j;

    // Compute using bottom-up DP
    for (int i = 2; i <= n; ++i) {
      for (int j = 1; j <= k; ++j) {
        int low = 1, high = j;
        int result = j;

        // Binary search for optimal floor to drop
        while (low <= high) {
          int mid = (low + high) / 2;
          int broken = dp[i - 1][mid - 1];    // Egg breaks
          int notBroken = dp[i][j - mid];     // Egg survives
          int worst = 1 + max(broken, notBroken);

          // Minimize the maximum number of moves
          if (broken > notBroken) {
            high = mid - 1;
          } else {
            low = mid + 1;
          }

          result = min(result, worst);
        }

        dp[i][j] = result;
      }
    }

    return dp[n][k];
  }
};
