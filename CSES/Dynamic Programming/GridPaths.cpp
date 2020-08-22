#include <iostream>
using namespace std;
#define ll long long
ll const mod=1e9+7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin>>n;
    char grid[n+1][n+1];
    for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) cin>>grid[i][j];
    ll dp[n+1][n+1];
    if (grid[1][1]=='.') dp[1][1]=1;
    else dp[1][1]=0;
    for (int i=2;i<=n;i++) {
        if (grid[i][1]=='*') dp[i][1]=0;
        else dp[i][1]=dp[i-1][1];
        if (grid[1][i]=='*') dp[1][i]=0;
        else dp[1][i]=dp[1][i-1];
    }
    for (int i=2;i<=n;i++) {
        for (int j=2;j<=n;j++) {
            if (grid[i][j]=='*') dp[i][j]=0;
            else dp[i][j]= (((grid[i][j-1]=='.')?dp[i][j-1]:0)+((grid[i-1][j]=='.')?dp[i-1][j]:0))%mod;
        }
    }
    cout<<dp[n][n];
    return 0;
}