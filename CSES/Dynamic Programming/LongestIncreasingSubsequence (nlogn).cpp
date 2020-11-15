#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin>>n;
    ll arr[n+1];
    for (int i=0;i<n;i++) cin>>arr[i];
    vector<ll> dp;
    dp.push_back(arr[0]);
    for (int i=1;i<n;i++) {
        int pos = lower_bound(dp.begin(), dp.end(), arr[i]) - dp.begin();
        if (pos==dp.size())
            dp.push_back(arr[i]);
        else
            dp[pos] = min(dp[pos], arr[i]);
    }
    cout<<dp.size();
    return 0;
}