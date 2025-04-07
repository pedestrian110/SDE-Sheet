/*
  Problem: Minimum Cost to Cut a Stick

  You're given a stick of length 'n' and a list of positions to cut called 'cuts'.
  The cost of a cut is equal to the length of the stick segment being cut.
  You can rearrange the order of cuts to minimize the total cost.

  ✅ Approaches Used:
  -------------------
  1. Top-Down (Recursive + Memoization)
  2. Bottom-Up (Dynamic Programming)

  -------------------------------------------
  Top-Down Explanation:
  - Add boundary cuts at positions 0 and n.
  - Sort the cuts array.
  - Use recursion to try all possible cut positions between two indices i and j.
  - At each cut, cost = (length of current stick segment) + cost of cutting left part + cost of cutting right part.
  - Store results in a memoization table to avoid recomputation.
  -------------------------------------------

  -------------------------------------------
  Bottom-Up Explanation:
  - Use a 2D DP table where dp[i][j] = minimum cost to cut between cuts[i] and cuts[j].
  - Fill the table diagonally (from small segments to larger ones).
  - For each segment, try all possible intermediate cuts and choose the minimum cost.
  -------------------------------------------
*/

class Solution {
 public:
  // Top-level function to call either approach
  int minCost(int n, vector<int>& cuts) {
    cuts.push_back(0);
    cuts.push_back(n);
    ranges::sort(cuts);

    // Uncomment either of the approaches:

    // ---------- Top-Down Approach ----------
    // vector<vector<int>> mem(cuts.size(), vector<int>(cuts.size(), INT_MAX));
    // return topDown(cuts, 0, cuts.size() - 1, mem);

    // ---------- Bottom-Up Approach ----------
    return bottomUp(cuts);
  }

 private:
  // Top-Down Recursive + Memoization
  int topDown(const vector<int>& cuts, int i, int j, vector<vector<int>>& mem) {
    if (j - i <= 1)
      return 0;  // No cuts possible in a segment of length ≤ 1
    if (mem[i][j] != INT_MAX)
      return mem[i][j];

    // Try every possible cut between i and j
    for (int k = i + 1; k < j; ++k)
      mem[i][j] = min(mem[i][j], cuts[j] - cuts[i] + 
                      topDown(cuts, i, k, mem) + topDown(cuts, k, j, mem));

    return mem[i][j];
  }

  // Bottom-Up DP Approach
  int bottomUp(const vector<int>& cuts) {
    int sz = cuts.size();
    vector<vector<int>> dp(sz, vector<int>(sz, 0));

    // d is the distance between i and j
    for (int d = 2; d < sz; ++d) {
      for (int i = 0; i + d < sz; ++i) {
        int j = i + d;
        dp[i][j] = INT_MAX;
        for (int k = i + 1; k < j; ++k)
          dp[i][j] = min(dp[i][j], cuts[j] - cuts[i] + dp[i][k] + dp[k][j]);
      }
    }

    return dp[0][sz - 1];  // Minimum cost to cut entire stick
  }
};
