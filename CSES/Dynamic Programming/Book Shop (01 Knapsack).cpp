#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n,x; cin>>n>>x;
    ll price[n+1], pages[n+1];
    for (int i=1;i<=n;i++) cin>>price[i];
    for (int i=1;i<=n;i++) cin>>pages[i]; 
    //Knapsack: To find a subset of items that has maximum value under given constraints
    //Items | atmost value -->
    //dp[i][j] = max(dp[i-1][j] , dp[i-1][j-price[i]] + pages[i] )
    ll dp[x+1]={0};
    for (int item=1;item<=n;item++) {
        for (int i=x;i>=1;i--) {
            if (i<price[item]) continue; //in this case dp[i][j]=dp[i-1][j] 
            dp[i] = max(dp[i], dp[i-price[item]]+pages[item]);
        }
    }
    cout<<dp[x]<<"\n";
    return 0;
}