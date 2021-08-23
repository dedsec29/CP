#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; cin>>n;
    vector<ll> arr(n);
    for (ll& i: arr) cin>>i;
    ll curr = 0;
    ll ans = arr[0];
    // at each step, curr ai can either extend the max subarray sum, or start new from here
    for (int i=0;i<n;i++) { 
        if (curr + arr[i] < arr[i]) 
            curr = arr[i];
        else
            curr += arr[i];
        ans = max(ans, curr);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}