#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n; cin>>n;
	vector<int> v;
	int coins[n], sum=0;
	for (int i=0;i<n;i++) cin>>coins[i], sum+=coins[i];
	//dp[i][x]=true if it is possible to make change for value of x with first i coins
	//true either if can make change for x with first i-1 coins itself, or make change for x-coins[i]
	//for x=0, we can always make change by giving no coin
	bool dp[sum+1]={false}; dp[0]=true;
	for (int j=0;j<n;j++) {
		for (int i=sum;i>=0;i--) {
			if (i>=coins[j])
				dp[i]=dp[i] || dp[i-coins[j]];
		}
	} 
	for (int i=1;i<=sum;i++) if (dp[i]) v.push_back(i);
	cout<<v.size()<<"\n";
	for (int i: v) cout<<i<<" ";
	return 0;
}