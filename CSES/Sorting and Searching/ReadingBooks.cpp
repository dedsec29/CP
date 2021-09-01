#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; cin>>n;
    ll sum = 0, mx = 0;
    for (int i=1;i<=n;i++) {
        ll r; cin>>r;
        sum += r;
        mx = max(r, mx);
    }
    if (mx >= sum-mx) cout << 2ll*mx;
    else cout << sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}