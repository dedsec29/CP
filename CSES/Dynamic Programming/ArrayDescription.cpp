#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll const mod= 1e9+7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m; cin>>n>>m;
    ll dp[n+1][m+2], arr[n+1];
    memset(dp,0,sizeof(dp));
    for (int i=1;i<=n;i++) cin>>arr[i];
    
    if (arr[1]==0) {//for when arr size 1 and ends with x
        for (int j=1;j<=m;j++) dp[1][j]=1;        
    }
    else dp[1][arr[1]]=1;
    
    for (int i=2;i<=n;i++) {
        for (int j=1;j<=m;j++) {
            if (arr[i]==0 || arr[i]==j)
                dp[i][j]= ((dp[i-1][j-1]+dp[i-1][j])%mod +dp[i-1][j+1])%mod;
        } 
    }
    ll ans=0;
    for (int i=1;i<=m;i++) ans=(ans+dp[n][i])%mod;
    cout<<ans;
    return 0;
}