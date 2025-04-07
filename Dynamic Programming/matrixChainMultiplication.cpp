/*
  🧠 Problem: Matrix Chain Multiplication

  You're given an array `arr[]` of size n, where the i-th matrix has dimensions:
  Matrix_i = (arr[i-1] x arr[i])

  Goal: Find the minimum number of scalar multiplications needed to multiply the entire chain of matrices.

  🔍 Approach: Dynamic Programming (Bottom-Up)

  1. Let `dp[i][j]` represent the minimum number of multiplications needed to multiply
     matrices from index `i` to `j` (1-based indexing of matrices).

  2. Initialize:
     - For all i, dp[i][i] = 0 → cost of multiplying one matrix is zero.

  3. Build the solution using increasing chain lengths `len` from 2 to n-1:
     - For each sub-chain starting at i and ending at j = i + len - 1:
         - Try every possible partition point k between i and j:
           dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + arr[i-1]*arr[k]*arr[j])
         - This breaks the problem into left and right matrix products and adds the cost of multiplying the result.

  4. The final result is dp[1][n-1], i.e., minimum cost to multiply all matrices from 1 to n-1.

  ⏱ Time Complexity: O(n^3)
  💾 Space Complexity: O(n^2)
*/

int matrixChainMultiplication(vector<int>& arr) {
    int n = arr.size(); // number of matrices = n - 1
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // len is the chain length (from 2 to n-1 matrices)
    for (int len = 2; len < n; ++len) {
        for (int i = 1; i < n - len + 1; ++i) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;

            // Try all positions to split the product
            for (int k = i; k < j; ++k) {
                int cost = dp[i][k] + dp[k+1][j] + arr[i-1] * arr[k] * arr[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[1][n - 1];
}
