/*
  Problem: Minimum Cost to Cut a Stick

  You're given a wooden stick of length `n` and an array `cuts[]` representing the positions where you need to make cuts.
  You can perform the cuts in any order.
  The cost of making a cut is equal to the length of the stick being cut at that moment.

  Goal: Minimize the total cost of all cuts.

  ✅ Approach: Dynamic Programming
  ----------------------------------
  1. Sort the `cuts` array and add the boundaries (0 and n) to create full segments.
     For example, if cuts = [1, 3, 4], and n = 7 → positions = [0, 1, 3, 4, 7]

  2. Define dp[i][j] = the minimum cost to cut the stick between positions[i] and positions[j]

  3. The recursive relation:
     For each possible cut between i and j (i+1 to j-1),
     the cost of cutting at position[k] = (positions[j] - positions[i]) + dp[i][k] + dp[k][j]

  4. Use bottom-up DP to fill dp[][].

  Time Complexity: O(m^3), where m = number of cuts + 2 (for added 0 and n)
*/

class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        // Step 1: Sort the cuts and include 0 and n
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());

        int m = cuts.size();
        vector<vector<int>> dp(m, vector<int>(m, 0));

        // Step 2: Fill the DP table bottom-up
        // len is the length of the segment (we go from small to large)
        for (int len = 2; len < m; ++len) {
            for (int i = 0; i + len < m; ++i) {
                int j = i + len;
                dp[i][j] = INT_MAX;

                // Step 3: Try every cut between i and j
                for (int k = i + 1; k < j; ++k) {
                    int cost = cuts[j] - cuts[i] + dp[i][k] + dp[k][j];
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }

        // Final answer is the cost to cut the full stick from 0 to n
        return dp[0][m - 1];
    }
};
