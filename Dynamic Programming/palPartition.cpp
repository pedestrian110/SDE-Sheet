/*
  🧠 Problem: Palindrome Partitioning (Min Cuts)

  You're given a string `s`. You need to partition it into substrings such that:
    - Every substring is a **palindrome**
    - Return the **minimum number of cuts** needed to make such a partitioning.

  🎯 Goal:
    Minimize the number of cuts such that every resulting substring is a palindrome.

  🔍 Approach: Dynamic Programming + Preprocessing Palindromes

  Step 1️⃣: Precompute all palindromic substrings
    - Use a 2D table `isPalindrome[i][j]` that tells if s[i..j] is a palindrome.
    - isPalindrome[i][j] = (s[i] == s[j]) && isPalindrome[i+1][j-1]

  Step 2️⃣: Define DP state
    - dp[i] = minimum cuts needed for the substring s[0..i]

  Step 3️⃣: DP Initialization
    - dp[0] = 0 (no cut needed for a 1-char palindrome)

  Step 4️⃣: Transition
    - If s[0..i] is a palindrome → no cut needed → dp[i] = 0
    - Else, try all j < i:
        If s[j+1..i] is palindrome → cut between j and j+1
        → dp[i] = min(dp[i], dp[j] + 1)

  ⏱ Time Complexity: O(n^2)
  💾 Space Complexity: O(n^2) for `isPalindrome`, O(n) for `dp`
*/

class Solution {
 public:
  int minCut(string s) {
    int n = s.length();
    
    // Step 1: Precompute palindromes
    vector<vector<bool>> isPalindrome(n, vector<bool>(n, false));
    for (int i = n - 1; i >= 0; --i) {
      for (int j = i; j < n; ++j) {
        if (s[i] == s[j] && (j - i < 2 || isPalindrome[i + 1][j - 1]))
          isPalindrome[i][j] = true;
      }
    }

    // Step 2: Initialize DP array
    vector<int> dp(n, INT_MAX);

    // Step 3: Fill DP
    for (int i = 0; i < n; ++i) {
      if (isPalindrome[0][i]) {
        dp[i] = 0;  // Whole substring [0..i] is a palindrome
      } else {
        for (int j = 0; j < i; ++j) {
          if (isPalindrome[j + 1][i])
            dp[i] = min(dp[i], dp[j] + 1);
        }
      }
    }

    // Step 4: Return result
    return dp[n - 1];
  }
};
