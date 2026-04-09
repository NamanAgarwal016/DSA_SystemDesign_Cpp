/*
UNBOUNDED KNAPSACK:
- Everthying similar to 0/1 knapsack, 
- ONLY we've unlimited supply of items.
- So if we like the item(wt[i-1] <= W), we can take it again, any no. of times.

Problem 1: Rod cutting problem
- given a Rod of length = 8,
- Can be cut into these pieces : {3, 5, 1, 2}
- For each piece, fixed value is given: {3->10, 5->6, 1->7, 2->12}
- Find max value earned by cutting & selling the rod.
SOLN: Exactly same as unbounded knapsack, no change
*/

#include <bits/stdc++.h>
using namespace std;

int unboundedKnapsack(vector<int> wt, vector<int> val, int W) {
    int n = wt.size();

    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    //same initiazlize
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= W; j++) 
            if(i == 0 || j == 0)
                dp[i][j] = 0;

    // main code
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= W; j++) {
            if(wt[i-1] > j)
                dp[i][j] = dp[i-1][j];
            else 
                dp[i][j] = max(dp[i-1][j], val[i-1] + dp[i][j - wt[i-1]]);  // ONLY dp[i-1] to dp[i] CHNAGE
        }
    }
    return dp[n][W];
}

int main(){
    vector<int> wt = {3, 5, 1, 2};              // Allowed cut-sizes
    vector<int> val = {10, 6, 7, 12};           // Price of each cut-piece
    int W = 8;                                  // Rod length

    cout << "Max value drawn: " << unboundedKnapsack(wt, val, W);
}