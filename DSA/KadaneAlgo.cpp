
/*
53. Maximum Subarray
Given an integer array nums, find the subarray with the largest sum, and return its sum.

Example 1:
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.
*/
class Solution {
public:
// Kadane's Algo
    int maxSubArray(vector<int>& nums) {
        int maxSum = INT_MIN;
        int n = nums.size();
        int i = 0;
        int sum = 0;
        while(i < n){
            sum += nums[i];
            maxSum = max(maxSum, sum);

            if(sum < 0) sum = 0;    // We'll not carry negative sum ahaead with us
            i++;    
        }
        return maxSum;
    }
};