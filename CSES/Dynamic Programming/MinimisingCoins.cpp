#include <bits/stdc++.h>
using namespace std;

int n,x;
int const inf=1e9;
int coins[100];

int solve(int value, vector<int>& dp) {
	if (value<0)
		return inf;
	if (value==0)
		return 0;

	if (dp[value]!=-1) return dp[value];

	int ans=inf;
	for (int i=0;i<n;i++)
		ans= min(solve(value-coins[i],dp)+1, ans);
	dp[value]=ans;
	return dp[value];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>n>>x;
	vector<int> dp(x+1, -1);
	for (int i=0;i<n;i++) cin>>coins[i];
	int ans=solve(x, dp);
	if (ans>=inf) cout<<"-1";
	else cout<<ans;
	return 0;
}