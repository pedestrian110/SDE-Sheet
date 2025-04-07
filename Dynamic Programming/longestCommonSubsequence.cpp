/*
  Problem:
  Given two strings text1 and text2, return the length of their longest common subsequence (LCS).

  Idea:
  Use Dynamic Programming (DP) to build up a solution.
  - Define dp[i][j] as the length of the LCS between:
      text1[0..i-1] and text2[0..j-1] (first i characters of text1 and first j of text2)

  Recurrence:
  - If characters match:        text1[i-1] == text2[j-1] 
      -> dp[i][j] = 1 + dp[i-1][j-1]
  - If not matching:
      -> dp[i][j] = max(dp[i-1][j], dp[i][j-1])
  This means we either skip a char from text1 or text2, whichever gives us a longer LCS.

  Time Complexity: O(m * n)
  Space Complexity: O(m * n)
*/

class Solution {
 public:
  int longestCommonSubsequence(string text1, string text2) {
    const int m = text1.length();  // Length of first string
    const int n = text2.length();  // Length of second string

    // Create a DP table of size (m+1) x (n+1)
    // dp[i][j] will store the LCS length of text1[0..i-1] and text2[0..j-1]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Fill the DP table
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (text1[i] == text2[j]) {
          // If characters match, extend the LCS from the previous characters
          dp[i + 1][j + 1] = 1 + dp[i][j];
        } else {
          // If they don't match, take the max LCS by excluding one char from either string
          dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
        }
      }
    }

    // The final answer is in dp[m][n], the full length of both strings
    return dp[m][n];
  }
};
