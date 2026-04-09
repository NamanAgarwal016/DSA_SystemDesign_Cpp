/*
UNBOUNDED KNAPSACK VARIATION:

Coin Change Problem:
- Given coins of denomination: 1, 2, 3 (Given unlimited supply of each coin)

Problem 1:
- Find total no. of ways by which sum of coins  = 5;
Sol: Exactly similar to Count subset sum problem (only unbounded knapsack chnage dp[i-1] to dp[i])
        dp[i][j] = dp[i-1][j] + dp[i][j - coins[i-1]]);

Problem 2:
- Find Min number of coins required to make sum = 5. 
Sol: dp[i][j] = min(dp[i-1][j], 1 + dp[i][j - coins[i-1]]);
*/

#include <bits/stdc++.h>
using namespace std;

int minCoins(vector<int> coins, int W) {
    int n = coins.size();
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    //INT_MAX initialzation
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= W; j++) {
            if(i == 0) dp[i][j] = INT_MAX - 1;
            if(j == 0) dp[i][j] = 0;
        }
            
    //2nd Row initialization is also needed here
    for(int j = 1; j <= W; j++) 
        if(j % coins[0] == 0)
            dp[1][j] = j / coins[0];
        else 
            dp[1][j] = INT_MAX - 1;

    for(int i = 2; i <= n; i++)
        for(int j = 1; j <= W; j++) 
            if(coins[i-1] > j)
                dp[i][j] = dp[i-1][j];
            else 
                dp[i][j] = min(dp[i-1][j], 1 + dp[i][j - coins[i-1]]);
    return dp[n][W];
}

int main() {
    vector<int> coins = {1, 2, 3};
    int sum = 5;

    cout << "Min coins required: " << minCoins(coins, sum) << endl;
}