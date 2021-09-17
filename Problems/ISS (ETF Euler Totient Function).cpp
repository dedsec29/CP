#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const K = 1e6;
int const siz = 4*K+1;
int phi[siz+1];
ll res[siz+1];  // Σ phi(i/d)*d

void precomputation() {
    phi[0] = 1;
    for (int i = 1; i <= siz; i++)
        phi[i] = i;
    for (int i = 2; i <= siz; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= siz; j += i) 
                phi[j] -= phi[j]/i;
        } 
    }
    for (int i = 1; i <= siz; i++) {
        for (int j = i; j <= siz; j += i)
            res[j] += ((ll) phi[j/i]) * ((ll) i);
    }
}

void solve() {
    ll k; cin>>k;
    ll ans = (res[4*k+1]+ 4ll*k - 1ll)/2;
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precomputation();
    int t; cin>>t;
    while (t--) 
        solve();
    return 0;
}