#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll const mod = 1e9+7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,x; cin>>n>>x;
    ll coins[n];
    for (int i=0;i<n;i++) cin>>coins[i];
    ll dp[x+1]={0}; dp[0]=1; //with any number of coins you can make change for 0 in 1 way: By giving no coins
	//coins | x ---->
	for (int j=0;j<n;j++) {
		for (int i=1;i<=x;i++)
			dp[i] = (dp[i] + (((i-coins[j])>=0)?dp[i-coins[j]]:0))%mod;
	}
	cout<<dp[x]<<"\n";
    return 0;
}