#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll const mod = 1e9+7;
// dp[n] = dp[2]dp[n-2] + dp[4]dp[n-4] + ... (till n/2 to avoid overcounting)
// this is same as recursive definition of Cn for sequence of length 2n
// Another way to think about this is: 
// Let ans = (2n)Cn  (this includes those too which have prefixes having more ')' than '(')
// Can we count them? Not so ezy, but..
// In all illegal sequences we included, there exists an integer k which is the first position
// where cnt('(') != cnt(')'). Now if we invert the brackets on the right of k, we will get a
// sequence having n-1 '('s and n+1 ')'s or the otherway around
// the function that does this inverting of brackets is bijective, so 
// n(sequences having prefixes having more ')' than '(')) = n(sequences having n+1 ')'s)
// Therefore overcounted value is (2n)C(n+1)
// and answer is (2n)C(n) - (2n)C(n+1) which is Cn = (1/(n+1)) (2n)C(n)

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
    int n; cin >> n;
    if (n&1) {
        cout << "0\n";
        return;
    }
    n >>= 1;
    ll nf = 1;
    for (ll i = 1; i <= n; i++) 
        nf = nf * i % mod;
    ll tnf = nf;
    for (ll i = n+1; i <= 2*n; i++)
        tnf = tnf * i % mod;
    ll x = poww(nf, mod-2);
    cout << ((tnf * (x * x % mod)) % mod) * poww(n+1, mod-2) % mod << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}