/*
  🧠 Problem: Minimum Path Sum (Grid-based DP)

  You're given an m x n grid filled with non-negative numbers.
  Your goal is to find a path from the top-left corner to the bottom-right corner
  such that the sum of all numbers along the path is minimized.

  You can only move **right** or **down** at any point.

  🔍 Approach: Dynamic Programming (In-place modification)

  1. Use the grid itself to store the minimum path sum to each cell.

  2. Base case:
     - grid[0][0] remains the same since it's the starting point.

  3. For the first row (i == 0), you can only come from the left (j - 1).
     So, accumulate the path sum horizontally.

  4. For the first column (j == 0), you can only come from above (i - 1).
     So, accumulate the path sum vertically.

  5. For all other cells (i > 0 && j > 0), take the **minimum** of the top and left cells,
     and add the current cell’s value.

  6. The final answer is at grid[m-1][n-1], which now contains the minimum path sum.

  ⏱ Time Complexity: O(m * n)
  💾 Space Complexity: O(1) (we're modifying the input grid itself)
*/

class Solution {
 public:
  int minPathSum(vector<vector<int>>& grid) {
    const int m = grid.size();
    const int n = grid[0].size();

    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
        if (i > 0 && j > 0)
          grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);  // From top or left
        else if (i > 0)
          grid[i][0] += grid[i - 1][0];  // First column, only from above
        else if (j > 0)
          grid[0][j] += grid[0][j - 1];  // First row, only from left

    return grid[m - 1][n - 1];  // Minimum path sum to bottom-right
  }
};
