/*
647. Palindromic Substrings
Given a string s, return the number of palindromic substrings in it.

A string is a palindrome when it reads the same backward as forward.

A substring is a contiguous sequence of characters within the string.

Example 1:
Input: s = "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
Example 2:

Input: s = "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

Constraints:
1 <= s.length <= 1000
s consists of lowercase English letters.

*/


//Approach-1 (Simply check all substrings possilbe)
//T.C : O(n^3)
//S.C : O(1)
class Solution {
public:

    bool check(string &s, int i, int j) {
        if(i >= j) 
            return true;
        if(s[i] == s[j]) 
            return check(s, i+1, j-1);
        return false;
    }

    int countSubstrings(string s) {
        int n = s.length();

        int count = 0;
        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) { //check all possible substrings
                if(check(s, i, j)) {
                    count++;
                }
            }
        }

        return count;
    }
};


//Approach-2 (Memoize the approach above)
//T.C : O(n^2) - Every subproblem is being computed only once and after that it's being reused
//S.C : O(n^2)
class Solution {
public:
    int t[1001][1001];
    bool check(string &s, int i, int j) {
        if(i >= j) {
            return true;
        }

        if(t[i][j] != -1) {
            return t[i][j]; //1 : True, 0 : False
        }

        if(s[i] == s[j]) {
            return t[i][j] = check(s, i+1, j-1);
        }

        return t[i][j] = false;

    }

    int countSubstrings(string s) {
        int n = s.length();
        memset(t, -1, sizeof(t));
        int count = 0;
        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) { //check all possible substrings
                if(check(s, i, j)) {
                    count++;
                }
            }
        }

        return count;
    }
};


//Approach-3(Bottom Up - My Favourite Blue Print of Pallindrome Qns)
//T.C : O(n^2)
//S.C ; O(n^2)
// This is BLUEPRINT for manyy palindromic Substring problems
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.length();
        int count = 0;
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        // State Defination: dp[i][j] = true means s[i to j] (both inclusive) is a palindromic substring

        for(int L = 1; L <= n; L++){
            for(int i = 0; i + L - 1 < n; i++){
                // the above termination condiion is for j < n
                int j = i + L - 1;

                // Length = 1 case, filling diagonals
                if(i == j) dp[i][j] = true;  

                // Length = 2 case, simply both element should be equal   
                else if(i+1 == j && s[i] == s[j]) dp[i][j] = true;

                // L > 2, genric case
                else dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1];
                
                if(dp[i][j]) count++;
            }
        }
        return count;
    }
};
