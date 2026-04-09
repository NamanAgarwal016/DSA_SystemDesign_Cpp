/*
Binary Search Template

Rule to Remember (Interview Gold)
Binary search with indices → always use <=
Because l == mid is a valid sorted range.
*/


#include <bits/stdc++.h>
using namespace std;

bool binarySearch(vector<int> arr, int target) {
    int n = arr.size();
    int lo = 0, hi = n-1;

    while(lo <= hi) {
        int mid = lo + (hi-lo)/2;

        if(arr[mid] < target)
            lo = mid + 1;
        else if(arr[mid] > target)
            hi = mid - 1;
        else 
            return true;
    }
    return false;
}


int main() {
    vector<int> arr = {7, 9, 17, 43, 77};
    int target = 9;

    cout << "Found: " << binarySearch(arr, target) << endl;
}