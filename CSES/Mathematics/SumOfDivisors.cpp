#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll const mod = 1e9+7;
ll const inv = 500000004;

ll range_sum(ll a,ll b) {
    a %= mod;
    b %= mod;
    if (a < 0) a += mod;
    ll x = b * (b + 1ll) % mod;
    ll y = a * (a - 1ll) % mod;
    x = x * inv % mod;
    y = y * inv % mod;
    ll ans = x - y;
    if (ans < 0) ans += mod;
    return ans;
}

void solve() {
    ll n; cin>>n;
    //ans = Σ(n/i)*i
    //[1, n] => [1, sqrt(n)] U [sqrt(n)+1, n]
    //A can give sqrt(n) unique n/is
    //if i in B, n/i <= sqrt(n) thus B gives sqrt(n) unique atmost vals
    //∴ there are atmost 2*sqrt(n) unique n/is. Need to find a way to iterate over these
    ll ans = 0;
    ll val = 1;
    while (val <= n) {
        ll q = n/val;
        ll nval = n/q + 1;  //next i giving new n/i (without +1 gives largest i giving that q)
        ans = (ans +  (range_sum(val, nval-1) * (q % mod) % mod) ) % mod;
        val = nval;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}