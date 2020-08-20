#include <iostream>
#include <vector>
using namespace std;
#define ll long long

int n;
ll const mod=1e9+7;

ll coins[100];

ll solve(ll value, vector<ll>& dp) {
	if (value==0) return 1;
	if (value<0) return 0;
	if (dp[value]!=-1) return dp[value];
	ll ans=0;
	for (int i=0;i<n;i++)
		ans = (ans + solve(value-coins[i], dp))%mod;
	dp[value]=ans;
	return dp[value];
}

int main() {
	int x; cin>>n>>x;
	for (int i=0;i<n;i++) cin>>coins[i];
	vector<ll> dp(x+1, -1);
	cout<<solve(x, dp);
}