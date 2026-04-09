/*
LIS
- Longest Increasing Subsequence
- This is strictly increasing

Bottom Up:
- This is not directly deducable from recursion
- Even dimension of dp is not 2, although 2 variables are changing in recursion, bcoz it's a different approach
- Classical example of DP: How to break into subproblem, then solve using previously solved.
- Define state first : dp[i] = LIS ending at i (Most Imp)
- TC: O[n^2]
- https://youtu.be/h9rm4N8XbL0?list=PLpIkg8OmuX-JhFpkhgrAwZRtukO0SkwAt
- https://youtu.be/fV-TF4OvZpk
 
Problem 1: If order is not needed to be maintained, basically not subsequence, find LIS
- So it becomes more easy now, just sort and find LIS after that.
- Why just sorting doesn't return ans, bcoz of these cases {10, 2, 2, 1, 7} -> LIS without order: 4

Problem 2: find the sum of LIS
- instead of fillinfg dp with 1 initially, fill with the same element: dp[i] = arr[i]
- 2nd, instead of { dp[i] = max(dp[i], 1 + dp[j]) }, 
        make it { dp[i] = max(dp[i], arr[i] + dp[j]) }

Problem 3: Print LIS
- store the parent idx from which we are obatining ans.
*/

#include <bits/stdc++.h>
using namespace std;

void PrintLis(vector<int> arr, int n) {
    vector<int> print;
    vector<int> prevIdx(n, -1);
    vector<int> dp(n, 1);
    int ans = 0;
    int prevMaxIdx = -1;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(arr[i] > arr[j]){
                if(dp[i] < 1 + dp[j]){
                    dp[i] = 1 + dp[j];
                    prevIdx[i] = j;
                }
            }
        }
        if(ans < dp[i]){
            ans = dp[i];
            prevMaxIdx = i;
        }
    }

    cout << "LIS max Length is: " << ans << endl;

    while(prevMaxIdx != -1) {
        print.push_back(arr[prevMaxIdx]);
        prevMaxIdx = prevIdx[prevMaxIdx];
    }
    reverse(print.begin(), print.end());
    for(int x: print)
        cout << x << " ";
}

int LisTopDown(vector<int> arr, int n) {
    vector<int> dp(n, 1);
    int ans = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++)
            if(arr[i] > arr[j])
                dp[i] = max(dp[i], 1 + dp[j]);
        ans = max(ans, dp[i]);
    }
    return ans;
}

int LisRecursiveMemoize(vector<int> arr, int n, int i, int prevTakenIdx, vector<vector<int>> &dp) {
    if(i >= n)
        return 0;
    
    if(prevTakenIdx != -1 && dp[i][prevTakenIdx] != -1)
        return dp[i][prevTakenIdx];

    int take = 0, notTake = 0;
    if(prevTakenIdx == -1 || arr[i] > arr[prevTakenIdx])
        take = 1 + LisRecursiveMemoize(arr, n, i+1, i, dp);
    notTake = LisRecursiveMemoize(arr, n, i+1, prevTakenIdx, dp);

    if(prevTakenIdx != -1)
        return dp[i][prevTakenIdx] = max(take, notTake);
    return max(take, notTake);
}

// prevTakenIdx to the Right of current idx
int LisRecursiveRightToLeft(vector<int> arr, int n, int prevTakenIdx) {
    if(n <= 0)
        return 0;

    int take = 0, notTake = 0;
    if(prevTakenIdx == -1 || arr[n-1] < arr[prevTakenIdx])
        take = 1 + LisRecursiveRightToLeft(arr, n-1, n-1);
    notTake = LisRecursiveRightToLeft(arr, n-1, prevTakenIdx);
    return max(take, notTake);
}

// prevTakenIdx to the Left of current idx
int LisRecursive(vector<int> arr, int n, int i, int prevTakenIdx) {
    if(i >= n)
        return 0;

    int take = 0, notTake = 0;
    if(prevTakenIdx == -1 || arr[i] > arr[prevTakenIdx])
        take = 1 + LisRecursive(arr, n, i+1, i);
    notTake = LisRecursive(arr, n, i+1, prevTakenIdx);
    return max(take, notTake);
}

int main() {
    vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    
    int n = arr.size();

    cout << "Length of LIS: " << LisRecursive(arr, n, 0, -1) << endl;
    cout << "Length of LIS: " << LisRecursiveRightToLeft(arr, n, -1) << endl;

    vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
    cout << "Length of LIS: " << LisRecursiveMemoize(arr, n, 0, -1, dp) << endl;

    cout << "Length of LIS: " << LisTopDown(arr, n) << endl;

    PrintLis(arr, n);
}