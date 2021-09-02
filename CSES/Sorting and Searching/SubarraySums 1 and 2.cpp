#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; ll x; cin>>n>>x;
    ll ans = 0, pf = 0;
    map<ll,ll> freq;
    for (int i=0;i<n;i++) {
        ll r; cin>>r;
        pf += r;
        if (pf == x) ans++;
        if (freq.count(pf-x))
            ans += freq[pf-x];
        freq[pf]++;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}