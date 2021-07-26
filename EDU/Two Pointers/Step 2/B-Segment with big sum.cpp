#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; cin>>n;
    ll s; cin>>s;
    ll arr[n];
    ll curr = 0;
    int ans = n+1;
    for (int i=0;i<n;i++) cin>>arr[i];
    for (int l=0,r=0;r<n;r++) {
        curr += arr[r];
        while (curr - arr[l] >= s) 
            curr -= arr[l++];
        if (curr >= s)
            ans = min(ans, r-l+1);
    }
    if (ans == n+1) cout<<"-1";
    else cout<<ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}