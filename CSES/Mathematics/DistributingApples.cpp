#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll const mod = 1e9+7;

ll poww(ll a,ll b) {
    a %= mod;
    ll res = 1;
    while (b) {
        if (b&1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n,m; cin>>n>>m;
    // apples that a child gets can be thought of as number of stars between bars
    // permutation of n-1 bars and m stars = (n+m-1)!/((n-1)!m!)
    // alternatively, x1 + x2 + .. + xn = (n+m-1)C(n-1)
    ll n1f, mf, nmf, num;
    n1f = mf = nmf = num = 1;
    for (ll i = 1; i <= n+m-1; i++) {
        num = num * i % mod;
        if (i == m)
            mf = num;
        if (i == n-1)
            n1f = num;
        if (i == n+m-1)
            nmf = num;
    }
    cout << (nmf * poww(n1f, mod-2) % mod) * poww(mf, mod-2) % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}