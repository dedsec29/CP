#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll const mod = 1e9+7;
int const siz = 1e6;
ll fact[siz+1], inv_fact[siz+1];

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

void compute_factorials() {
    fact[0] = 1;
    for (ll i = 1; i <= siz; i++)
        fact[i] = fact[i-1] * i % mod;
}

void compute_inv_factorials() {
    inv_fact[siz] = poww(fact[siz], mod-2);
    for (ll i = siz-1; i >= 0; i--)
        inv_fact[i] = inv_fact[i+1] * (i+1) % mod;
}

ll Binomial(ll n,ll r) {
    if (n < r || r < 0)
        return 0;
    return (fact[n] * inv_fact[n-r] % mod) * inv_fact[r] % mod;
}

void precomputation() {
    compute_factorials();
    compute_inv_factorials();
}

void solve() {
    string s; cin>>s;
    int n = s.size();
    vector<int> freq(26);
    for (char c: s) freq[c-'a']++;
    ll ans = fact[n];
    for (int i: freq)
        ans = ans * inv_fact[i] % mod;
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precomputation();
    solve();
    return 0;
}