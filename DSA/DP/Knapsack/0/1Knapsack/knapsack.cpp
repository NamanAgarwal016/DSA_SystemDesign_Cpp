/*
0/1 Knapsack

Ques:
    Given Knapsack Weight W, total n stones, with wt[] & val[]
    Find the max val, that can be picked in knapsack.
Soln:
    Recursive:
        2 options for each stones: take & not-take
        base cond: n==0 || W==0 return 0;
        Assume we have answer if we have 0 to n-2 stones, Now check with last n-1 stone: take or not take
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
    int knapsackTopDown(int n, int W, vector<int> wt, vector<int> val) {
        vector<vector<int>> dp(n+1, vector<int>(W+1));

        for(int i = 0; i <= n; i++)
            for(int j = 0; j <= W; j++)
                if(i == 0 || j == 0)
                    dp[i][j] = 0;

        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= W; j++)
                if(wt[i-1] > j)
                    dp[i][j] = dp[i-1][j];
                else
                    dp[i][j] = max(dp[i-1][j], val[i-1] + dp[i-1][j-wt[i-1]]);

        return dp[n][W];
    }

    int knapsackMemoize(int n, int W, vector<int> wt, vector<int> val, vector<vector<int>> &dp) {
        if (n == 0 || W == 0)
            return dp[n][W] = 0;
        
        if(dp[n][W] != -1)
            return dp[n][W];

        if (wt[n - 1] > W)
            return dp[n][W] = knapsackMemoize(n - 1, W, wt, val, dp);
        else
            return dp[n][W] = max(
                knapsackMemoize(n - 1, W, wt, val, dp),
                val[n - 1] + knapsackMemoize(n - 1, W - wt[n - 1], wt, val, dp));
    }

    int knapsackRecursive(int n, int W, vector<int> wt, vector<int> val) {
        if (n == 0 || W == 0)
            return 0;

        if (wt[n - 1] > W)
            return knapsackRecursive(n - 1, W, wt, val);
        else
            return max(
                knapsackRecursive(n - 1, W, wt, val),
                val[n - 1] + knapsackRecursive(n - 1, W - wt[n - 1], wt, val));
    }
};


int main()
{
    int W = 15, n = 5;
    vector<int> wt = {2, 5, 9, 4, 1};
    vector<int> val = {50, 27, 5, 67, 8};

    Solution solver;
    // Solution* solver = new Solution();   // not preffered, as m=we need to deleted this pointer as well

    cout << "Max value collected in knapsack: " << solver.knapsackRecursive(n, W, wt, val) << endl;

    vector<vector<int>> dp(n+1, vector<int>(W+1, -1));
    cout << "Max value collected in knapsack: " << solver.knapsackMemoize(n, W, wt, val, dp) << endl;

    cout << "Max value collected in knapsack: " << solver.knapsackTopDown(n, W, wt, val) << endl;
}