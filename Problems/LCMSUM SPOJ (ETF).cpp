#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const siz = 1e6;
int phi[siz+1];
ll res[siz+1];  // Σ d * phi(d) of i

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
            res[j] += ((ll) i) * ((ll) phi[i]);
    }
}

void solve() {
    ll n; cin>>n;
    ll s = (n + n * res[n])/2;
    cout << s << "\n";
    //code n code's explanation
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