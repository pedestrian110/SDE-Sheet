/*
  Problem: Word Break

  Given a string `s` and a dictionary of words `wordDict`, determine if `s` can be segmented into a 
  space-separated sequence of one or more dictionary words.

  ✅ Approach 1: Top-down recursion with memoization and string passing
    - Try every prefix.
    - If the prefix is in the dictionary and suffix can be segmented (recursively), return true.
    - Memoize results for substrings to avoid recomputation.
*/

class Solution1 {
 public:
  bool wordBreak(string s, vector<string>& wordDict) {
    return wordBreak(s, {wordDict.begin(), wordDict.end()}, {});
  }

 private:
  bool wordBreak(const string& s, const unordered_set<string>&& wordSet,
                 unordered_map<string, bool>&& mem) {
    if (wordSet.contains(s)) return true;
    if (auto it = mem.find(s); it != mem.cend()) return it->second;

    for (int i = 1; i < s.length(); ++i) {
      string prefix = s.substr(0, i);
      string suffix = s.substr(i);
      if (wordSet.contains(prefix) &&
          wordBreak(suffix, wordSet, mem))
        return mem[s] = true;
    }

    return mem[s] = false;
  }
};

/*
  ✅ Approach 2: Top-down recursion with memoization using index
    - Avoids string copying, more efficient.
    - Try each possible break point from current index.
    - Memoize using the index to avoid redundant checks.
*/

class Solution2 {
 public:
  bool wordBreak(string s, vector<string>& wordDict) {
    return wordBreak(s, 0, {wordDict.begin(), wordDict.end()},
                     vector<int>(s.length(), -1));
  }

 private:
  bool wordBreak(const string& s, int i, const unordered_set<string>&& wordSet,
                 vector<int>&& mem) {
    if (i == s.length()) return true;
    if (mem[i] != -1) return mem[i];

    for (int j = i + 1; j <= s.length(); ++j)
      if (wordSet.contains(s.substr(i, j - i)) &&
          wordBreak(s, j, wordSet, mem))
        return mem[i] = 1;

    return mem[i] = 0;
  }
};

/*
  ✅ Approach 3: Bottom-up DP (Tabulation)
    - dp[i] = true if s[0..i) can be segmented using words in dictionary.
    - Try every possible j < i, and check if s[j..i) is a valid word and dp[j] is true.
*/

class Solution3 {
 public:
  bool wordBreak(string s, vector<string>& wordDict) {
    int n = s.length();
    unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (dp[j] && wordSet.contains(s.substr(j, i - j))) {
          dp[i] = true;
          break;
        }
      }
    }

    return dp[n];
  }
};

/*
  ✅ Approach 4: Bottom-up DP with optimization using max word length
    - Same as Approach 3 but avoids unnecessary substring checks.
    - Only check substrings up to the max length of any word in dictionary.
*/

class Solution4 {
 public:
  bool wordBreak(string s, vector<string>& wordDict) {
    int n = s.length();
    int maxLength = getMaxLength(wordDict);
    unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
    vector<int> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; ++i) {
      for (int j = i - 1; j >= 0; --j) {
        if (i - j > maxLength) break;
        if (dp[j] && wordSet.contains(s.substr(j, i - j))) {
          dp[i] = true;
          break;
        }
      }
    }

    return dp[n];
  }

 private:
  int getMaxLength(const vector<string>& wordDict) {
    int maxLen = 0;
    for (const auto& word : wordDict)
      maxLen = max(maxLen, static_cast<int>(word.length()));
    return maxLen;
  }
};
