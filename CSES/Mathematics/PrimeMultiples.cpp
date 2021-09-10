#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    ll n; int k; cin>>n>>k;
    vector<ll> v(k+1), p(k);
    for (ll& i: p) cin>>i;
    int ub = 1<<k;
    for (int i=1;i<ub;i++) {
        ll f = 1;
        bool overflow = false;
        int pcnt = 0;
        for (int j=0;j<k;j++) {
            if (i & (1<<j)) {
                pcnt++;
                if (f <= n/p[j])
                    f *= p[j];
                else {
                    overflow = true;
                    break;
                }
            }
        }
        if (overflow)
            continue;
        v[pcnt] += n/f;
    }
    ll ans = 0;
    for (int i=1;i<=k;i++) {
        if (i&1)
            ans += v[i];
        else
            ans -= v[i];
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}