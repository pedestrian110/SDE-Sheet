/*
  Problem:
  Given an integer array nums, find the contiguous subarray (containing at least one number) 
  which has the largest product and return its product.

  Why this approach?
  - A simple running product won't work due to presence of negative numbers and zeros.
  - Multiplying by a negative number flips max to min and vice versa.
  - So, at each step, we track both:
      1. Maximum product ending at current index.
      2. Minimum product ending at current index.
  - This ensures that if a large negative product becomes positive due to a new negative number, 
    we don't miss it.

  DP States:
  - dpMax: maximum product ending at current index
  - dpMin: minimum product ending at current index

  Transition:
  - If current number is negative, we swap previous dpMin and dpMax before using them.
  - Update:
      dpMax = max(num, prevMax * num, prevMin * num)
      dpMin = min(num, prevMax * num, prevMin * num)

  Time Complexity: O(n)
  Space Complexity: O(1) — we use only two variables for state
*/

class Solution {
 public:
  int maxProduct(vector<int>& nums) {
    // Initialize the answer and both states with the first element
    int ans = nums[0];
    int dpMin = nums[0];  // The minimum product ending at current index
    int dpMax = nums[0];  // The maximum product ending at current index

    // Iterate through the array starting from index 1
    for (int i = 1; i < nums.size(); ++i) {
      const int num = nums[i];

      // Store previous values for reference
      const int prevMin = dpMin;
      const int prevMax = dpMax;

      // If the current number is negative, it could flip the min and max
      if (num < 0) {
        dpMin = min(prevMax * num, num);
        dpMax = max(prevMin * num, num);
      } else {
        dpMin = min(prevMin * num, num);
        dpMax = max(prevMax * num, num);
      }

      // Update the global maximum product found so far
      ans = max(ans, dpMax);
    }

    return ans;
  }
};
