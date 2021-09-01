#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll unsigned long long

void solve() {
    int n; ll k; cin>>n>>k;
    vector<ll> t(n+1);
    for (int i=1;i<=n;i++) cin>>t[i];
    sort(t.begin(),t.end());
    ll l = 0, r = (t.back() * k) + 1ll;
    while (r-l > 1) {
        ll mid = (l+r)>>1;
        ll units = 0;
        for (int i=1;i<=n;i++)
            units += mid/t[i];
        if (units < k)
            l = mid;
        else
            r = mid;
    }
    cout << r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}