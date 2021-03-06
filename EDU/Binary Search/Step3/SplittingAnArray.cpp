#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,k; cin>>n>>k;
    ll arr[n+1];
    for (int i=1;i<=n;i++) cin>>arr[i];
    ll presum[n+1];
	presum[0] = 0;
	for (int i=1;i<=n;i++)
		presum[i] = presum[i-1] + arr[i];
	ll l=0, r = n*1ll*1e9 + 1ll;
	 
    return 0;
}