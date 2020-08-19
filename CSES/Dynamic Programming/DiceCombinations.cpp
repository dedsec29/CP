#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll const mod=1e9+7;

int main() {
	int n; cin>>n;
	vector<ll> dp(max(7,n+1)); dp[0]=1;
	for (int i=1;i<=6;i++) {
		for (int j=0;j<i;j++) dp[i]=(dp[i]+dp[j])%mod;
	}
	if (n<=6) cout<<dp[n];
	else {
		for (int i=7;i<=n;i++)
			dp[i]=(((2ll*dp[i-1])%mod-dp[i-7])%mod+mod)%mod;
		cout<<dp[n];
	}
	return 0;
}