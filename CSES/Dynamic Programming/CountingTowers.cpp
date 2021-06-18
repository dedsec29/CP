#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll const mod = 1e9+7;
int const siz = 1e6;
ll dp[2][siz+1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //dp[0][i] = number of ways to tile till height i such that (i-1)th was united
    //dp[1][i] = number of ways to tile till height i such that (i-1)th was piped
    dp[0][1] = dp[1][1] = 1;
    for (int i=1;i<siz;i++) {
        dp[0][i+1] = (dp[1][i] + (2ll*dp[0][i])%mod)%mod;   //:|, ||, []
        dp[1][i+1] = ((4ll*dp[1][i])%mod + dp[0][i])%mod;   //.-., '_', ::, |:, =
    }
    int t; cin>>t;
    while (t--) {
        int q; cin>>q;
        cout<<(dp[0][q]+dp[1][q])%mod<<"\n";
    }
    return 0;
}