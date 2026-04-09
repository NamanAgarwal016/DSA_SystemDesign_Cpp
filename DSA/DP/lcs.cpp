/*
LCS: longest common subsequence

- given 2 strings "abcdgh" & "abedfhr"
- find length of longest common subsequence(not continuous but maintains order)

Problem1 : Print LCS
- analyze how lcs is working, how it's filling data in dp
- How dp is fllied in lCS:
    - if matched, current cell = up digonal cell + 1
    - if unmatched, current cell = left or up cell according to the max value.
- For printing lcs, follow in reverse order after filling dp
- starting from last bottom: dp[n][m]
- if matched, print letter & move diagonally up
- if not matched, don't print anything & move left or up acc to max value in dp cell.

Problem2: Length of SCS
- Shortest Common SuperSequence  (shortest string having both the subsequence)
- s1 = "geek" s2 = "eke" : SCS = "geeke"
- so if we want shortest, then we have to write LCS only one time (which is common in both actually) and rest letters exactly one time.
- SCS = n + m - LCS 

Problem3: Print SCS
- Similar to Print LCS
- Only diff: if not matched, then print smaller one, and move to larger one.

Problem4: Min no. of Insertions & Deletions to convert string s1 to s2
- s1 = "heap" s2 = "pea" : 
- ans = from "heap" first delete "h" & "p", and then insert "p" : 2 deletion & 2 insertion
- Sol: Convert s1 to s2 via LCS
- going from s1 to LCS will give #Deletions = n - LCS;
- going from LCS to s2 will give #Insertions = m - LCS;

Problem5: Length of LPS
- Longest Palindromic Subsequence
- s1 = "agbcba": ans = len("abcba") = 5
- Soln: LCS has two string, but here it is only 1, where's other?
- s1 = "agbcba" s2 = reverse(s1) = "abcbga" : now find LCS to get LPS
- LPS(s1) = LCS(s1, reverse(s1))

Problem6: Min no. of deletions to make a string palidrome
- s1 "agbcba"  --> ans: "abcba" #deletion = 1
- To minimize $deletions, we want LPS
- Min #deletions = s1.length() - LPS(s1)
- Also, Min no. of insertion to make it palindrome = 1 (agbcbga) = s1.length() - LPS(s1) = #deletions

Problem7: Length of LRS
- Longest Repeating Subsequence
- from a given str, find two subsequnces(not continuous, but ordered) which have same letters in same order but not the same position
- Given s1 = "AABCABB", ans: "AABB"  "AABB"
    Postion:  0123456         0125    1456  
- Soln: find LCS(s1, s1) of same string but with a cond, that if matched check if i != j

Problem8: length of Longest Common Substring
- substring is continuous, with maintained order. Subsequence can be non-continuous
- s1 = "abcde", s2 = "abfce"; ans: "ab" 
- soln: when unmatched, stop there it self, by making length = 0
*/

#include <bits/stdc++.h>
using namespace std;

// Can't covert this to Top down Dp
int lcSubstringRecursive(string s1, string s2, int n, int m, int len) {
    if(n == 0 || m == 0)
        return len;

    if(s1[n-1] == s2[m-1])
        len = lcSubstringRecursive(s1, s2, n-1, m-1, len+1);
    else 
        len = max(len, max(lcSubstringRecursive(s1, s2, n-1, m, 0), lcSubstringRecursive(s1, s2, n, m-1, 0)));
        
    return len;
}

int lcSubstringTopDown(string s1, string s2, int n, int m) {
    int ans = 0;

    // Initialization & base cond as well
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= m; j++)
            if(s1[i - 1] == s2[j - 1]){
                dp[i][j] = 1 + dp[i-1][j-1];
                ans = max(ans, dp[i][j]);
            } else 
                dp[i][j] = 0;           // ONLY CHANGE

    // Space optimization, as we're only using 2 rows
    // vector<vector<int>> dp(2, vector<int>(m+1, 0));
    // for(int i = 1; i <= n; i++) 
    //     for(int j = 1; j <= m; j++) 
    //         if(s1[i - 1] == s2[j - 1]){
    //             dp[i%2][j] = 1 + dp[(i-1) % 2][j-1];
    //             ans = max(ans, dp[i%2][j]);
    //         } else 
    //             dp[i%2][j] = 0;
        
    return ans;
}

int lrsTopDown(string s1, int n) {
    // same LCS initialzation
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= n; j++)
            if(s1[i-1] == s1[j-1] && i != j)            // ONLY CHNAGE
                dp[i][j] = 1 + dp[i-1][j-1];
            else 
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    return dp[n][n];
}

string printScs(string s1, string s2, int n, int m) {
    string ans;

    //Same code as LCS
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else 
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

    //Print code
    int i = n, j = m;
    while(i >= 1 && j >= 1) {
        if(s1[i-1] == s2[j-1]){
            ans += s1[i-1];
            i--; j--;
        } else {
            if(dp[i-1][j] > dp[i][j-1]){
                ans += s1[i-1];                 // ONLY CHANGE: print what we're leaving
                i--;
            } else {
                ans += s2[j-1];                 // ONLY CHANGE: print what we're leaving
                j--;    
            }
        }
    }
    while(i >= 1){
        ans += s1[i-1];                         // if i is still remaining 
        i--;
    }
    while(j >= 1){                               // if j is still remaining
        ans += s2[j-1];
        j--;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

string printLcs(string s1, string s2, int n, int m) {

    //1st simple lcs code only
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else 
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

    // Now print code
    string ans;
    int i = n, j = m;
    while(i >= 1 && j >= 1){
        if(s1[i-1] == s2[j-1]){
            ans += s1[i-1];
            i--; j--;
        } else {
            if(dp[i-1][j] > dp[i][j-1])
                i--;
            else
                j--;
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int lcsTopDown(string s1, string s2, int n, int m) {

    vector<vector<int>> dp(n+1, vector<int>(m+1));

    //Base cond
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= m; j++)
            if(i == 0 || j == 0)
                dp[i][j] = 0;

    //main code
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) 
            if(s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else 
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

    return dp[n][m];
}

int lcsMemoize(string s1, string s2, int n, int m, vector<vector<int>> &dp) {
    //Base cond
    if(n == 0 || m == 0) 
        return 0;

    if(dp[n][m] != -1)
        return dp[n][m];

    // main code
    if(s1[n-1] == s2[m-1])
        return dp[n][m] = 1 + lcsMemoize(s1, s2, n-1, m-1, dp);
    else
        return dp[n][m] = max(lcsMemoize(s1, s2, n-1, m, dp), lcsMemoize(s1, s2, n, m-1, dp));
}

int lcsRecursive(string s1, string s2, int n, int m) {
    //Base cond
    if(n == 0 || m == 0) 
        return 0;

    // main code
    if(s1[n-1] == s2[m-1])
        return 1 + lcsRecursive(s1, s2, n-1, m-1);
    else
        return max(lcsRecursive(s1, s2, n-1, m), lcsRecursive(s1, s2, n, m-1));
}

int main() {
    string s1 = "abcdgh", s2 = "abedfhr";
    int n = s1.length(), m = s2.length();

    cout << "Length of LCS: " << lcsRecursive(s1, s2, n, m) << endl;

    vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
    cout << "Length of LCS: " << lcsMemoize(s1, s2, n, m, dp) << endl;

    cout << "Length of LCS: " << lcsTopDown(s1, s2, n, m) << endl;

    cout << "Print LCS: " << printLcs(s1, s2, n, m) << endl;
    cout << endl;

    cout << "Length of SCS: " << (n + m - lcsTopDown(s1, s2, n, m)) << endl;

    cout << "Print SCS: " << printScs(s1, s2, n, m) << endl;
    cout << endl;

    s1 = "agbcba";
    s2 = s1;
    reverse(s2.begin(), s2.end());
    cout << "Length of LPS: " << lcsTopDown(s1, s2, s1.length(), s2.length()) << endl;
    cout << endl;

    s1 = "AABCABB";
    cout << "Length of LRS: " << lrsTopDown(s1, s1.length()) << endl;
    cout << endl;

    s1 = "abcde", s2 = "abfce";
    cout << "Length of LCSubstring: " << lcSubstringTopDown(s1, s2, s1.length(), s2.length()) << endl;

    int len = 0;
    cout << "Length of LCSubstring: " << lcSubstringRecursive(s1, s2, s1.length(), s2.length(), len) << endl;

    cout << endl;
    return 0;
}