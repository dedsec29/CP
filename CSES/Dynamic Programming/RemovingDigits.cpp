#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int solve(int n, vector<int>& dp) {
    if (n<0) return 1e8;
    if (n==0) return 0;
    if (dp[n]!=-1) return dp[n];
    int x=n, ans=1e8;
    while (x) { 
        int d= x%10;
        if (d!=0) ans=min(ans, solve(n-d, dp)+1);
        x=x/10;
    }
    dp[n]=ans;
    return dp[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin>>n;
    vector<int> dp(n+1,-1);
    cout<<solve(n, dp);
    return 0;
}