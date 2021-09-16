#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll const mod = 1e9+7;
int siz;
vector<ll> fact, inv_fact;
 
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

ll derangement(ll n) {
    ll ans = 0;
    for (int i=0;i<=n;i++) {
        if (i&1) {
            ans -= inv_fact[i];
            if (ans < 0) ans += mod;
        }
        else
            ans = (ans + inv_fact[i]) % mod;
    }
    ans = ans * fact[n] % mod;
    return ans;
}

void solve() {
    cin >> siz;
    fact.assign(siz+1, 0);
    inv_fact.assign(siz+1, 0);
    compute_factorials();
    compute_inv_factorials();
    cout << derangement(siz);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}