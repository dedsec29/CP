#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll const mod = 1e9+7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin>>n;
    ll x = n*(n+1);
    if (x%4!=0) {
        cout<<0;
        return 0;
    }
    x /= 4;
    ll dp[n+1][x+1];
    dp[0][0] = 1;
    for (int i=1;i<=x;i++) dp[0][i] = 0;
    for (int i=1;i<=n;i++) dp[i][0] = dp[i-1][0];
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=x;j++)
            dp[i][j] = (dp[i-1][j] + ((j>=i)?dp[i-1][j-i]:0))%mod;
    }
    cout<<(dp[n][x]*500000004)%mod;
    return 0;
}