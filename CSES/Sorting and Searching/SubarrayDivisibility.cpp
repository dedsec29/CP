#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    ll n; cin>>n;
    ll ans = 0, pf = 0;
    vector<ll> freq(n);
    for (int i=0;i<n;i++) {
        ll r; cin>>r;
        r = r%n;
        if (r < 0) r += n;
        pf = (pf + r)%n;
        if (pf == 0) ans++; //always remember this case in such problems
        ans += freq[pf];
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