/*
  Problem: Coin Change

  You're given a list of coin denominations and a total amount.
  Your task is to find the minimum number of coins needed to make up that amount.
  If it's not possible to make the amount, return -1.

  ✅ Common Concepts:
  ---------------------
  - Use Dynamic Programming to solve the problem efficiently.
  - Define dp[i] as the minimum number of coins needed to make amount 'i'.
  - Initialize dp[0] = 0 (0 coins needed to make amount 0).
  - Initialize all other dp[i] to a large value (amount + 1), since we want to minimize.

  🔁 Two Equivalent Iteration Orders:
  -----------------------------------
  Approach 1: Outer loop over coins, inner loop over all amounts from coin to amount
      - For each coin, update the dp table for all values that coin can contribute to.
      - Ensures that each amount considers current coin and earlier results.

  Approach 2: Outer loop over amount, inner loop over all coins
      - For each amount, try using every coin to build up that amount.
      - Ensures that all combinations are checked to form amount 'i'.

  Both approaches build up the dp table by checking:
    dp[i] = min(dp[i], dp[i - coin] + 1)

  🚩 Final Step:
  - If dp[amount] is still equal to (amount + 1), that means the amount cannot be formed.
  - Otherwise, return dp[amount] as the minimum number of coins.
*/

class Solution {
 public:
  int coinChange(vector<int>& coins, int amount) {
    // dp[i] := minimum number of coins to make amount i
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;  // Base case: 0 coins to make amount 0

    // You can use either of the two loop orders:

    // ----- Version 1: For each coin, update possible amounts -----
    for (const int coin : coins)
      for (int i = coin; i <= amount; ++i)
        dp[i] = min(dp[i], dp[i - coin] + 1);

    // ----- Version 2: For each amount, try all coins -----
    /*
    for (int i = 1; i <= amount; ++i)
      for (const int coin : coins)
        if (coin <= i)
          dp[i] = min(dp[i], dp[i - coin] + 1);
    */

    // If dp[amount] is unchanged, return -1 (not possible)
    return dp[amount] == amount + 1 ? -1 : dp[amount];
  }
};
