/*
  🧠 Problem: Edit Distance (Levenshtein Distance)

  You're given two strings: word1 and word2.
  You need to find the **minimum number of operations** (insert, delete, replace)
  required to convert word1 into word2.

  🔍 Approach: Dynamic Programming (Bottom-Up)

  1. Define dp[i][j] as the minimum number of operations required to convert:
     - word1[0..i-1] to word2[0..j-1]
  2. Dimensions of dp: (m+1) x (n+1) where m = length of word1, n = length of word2
  3. Base Cases:
     - dp[0][j] = j → converting empty string to word2[0..j-1] needs j insertions
     - dp[i][0] = i → converting word1[0..i-1] to empty string needs i deletions
  4. Transitions:
     - If word1[i-1] == word2[j-1] → characters match → no operation needed:
       dp[i][j] = dp[i-1][j-1]
     - Else → characters differ → take the minimum of:
       a. Replace → dp[i-1][j-1]
       b. Delete  → dp[i-1][j]
       c. Insert  → dp[i][j-1]
       Add 1 to the chosen operation

  ✅ Final Answer: dp[m][n] = minimum operations to convert full word1 to word2

  ⏱ Time Complexity: O(m * n)
  💾 Space Complexity: O(m * n)
*/

class Solution {
 public:
  int minDistance(string word1, string word2) {
    const int m = word1.length();
    const int n = word2.length();

    // dp[i][j] := min operations to convert word1[0..i) to word2[0..j)
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // Fill base case: converting word1[0..i) to empty string
    for (int i = 1; i <= m; ++i)
      dp[i][0] = i;

    // Fill base case: converting empty string to word2[0..j)
    for (int j = 1; j <= n; ++j)
      dp[0][j] = j;

    // Fill the rest of the table
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (word1[i - 1] == word2[j - 1]) {
          // No operation needed if characters match
          dp[i][j] = dp[i - 1][j - 1];
        } else {
          // Choose the best among replace, delete, insert
          dp[i][j] = min({
            dp[i - 1][j - 1],  // Replace
            dp[i - 1][j],      // Delete
            dp[i][j - 1]       // Insert
          }) + 1;
        }
      }
    }

    return dp[m][n];
  }
};
