/*
0/1 KNAPSACK VARIATION:

Problem 1:
Subset Sum Problem
- Knapsacl 0/1 problem
- Given arr[] with +ve nos, and a Sum, return T/F if there exist any subset(means non-contiguous) with sum = Sum

Problem 2:
- Count number of subsets with given sum
- Knapsack0/1 -> Subset Sum -> This problem

Problem 3:
- Given arr, break into 2 subests having sum s1 & s2, Return min(s1-s2)
- Exactly similar prob: https://leetcode.com/problems/last-stone-weight-ii/description/
*/

#include <bits/stdc++.h>
using namespace std;

int minSubsetSum(vector<int> arr) {
    int n = arr.size();

    //Here we need to pass TotalSum as W value in subset sum prob
    int range = 0;     
    for(int x: arr) range += x;
    int W = range;
    
    vector<vector<bool>> dp(n+1, vector<bool>(W+1));

    // initialzation: exactly similar to subsetsum
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= W; j++) {
            if(i == 0) dp[i][j] = false;
            if(j == 0) dp[i][j] = true;
        }
    }

    // real code: exactly similar to subsetsum
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= W; j++) {
            if(arr[i-1] > j)
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = dp[i-1][j] || dp[i-1][j-arr[i-1]];
        }
    }

    // Now use last row : dp[n]
    
    int s1 = 0;
    int minDiff = range - 2*s1;
    // for minimizing diff, maximize s1( which is 0 to range/2) if possible(get from subset sum prob last row)
    for(s1 = range/2; s1 >= 0; s1--){
        if(dp[n][s1] == true){
            return range - 2*s1;
        }
    }
    return minDiff;
}

int countSubsetSum(vector<int> arr, int sum) {
    int n = arr.size();
    int W = sum;
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    // initialzation
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= W; j++) {
            if(i == 0) dp[i][j] = 0;
            if(j == 0) dp[i][j] = 1;
        }
    }

    // real code
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= W; j++) {
            if(arr[i-1] > j)
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = dp[i-1][j] + dp[i-1][j-arr[i-1]];    // ONLY THIS CHANGE :)
        }
    }

    return dp[n][W];
}

bool subsetSum(vector<int> arr, int sum) {
    int n = arr.size();
    int W = sum;
    vector<vector<bool>> dp(n+1, vector<bool>(W+1));

    // initialzation
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= W; j++) {
            if(i == 0) dp[i][j] = false;
            if(j == 0) dp[i][j] = true;
        }
    }

    // real code
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= W; j++) {
            if(arr[i-1] > j)
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = dp[i-1][j] || dp[i-1][j-arr[i-1]];
        }
    }

    return dp[n][W];
}

int main() {
    vector<int> arr = {2, 3, 5, 6, 8, 10};
    int sum = 10;

    cout << "Subset sum possible: " << subsetSum(arr, sum) << endl;

    cout << "Number of subsets with given sum: " << countSubsetSum(arr, sum) << endl;

    cout << "Minimum Subset sum differnece possible is: " << minSubsetSum(arr) << endl;
}





