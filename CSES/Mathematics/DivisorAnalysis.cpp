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

ll sigma(ll p,ll k) {
    ll a = poww(p, k+1) - 1ll;
    if (a < 0) a += mod;
    ll b = poww(p-1ll, mod-2);
    return a * b % mod;
}

void solve() {
    int n; cin>>n;
    vector<pair<ll,ll>> arr(n);
    ll d = 1, sum = 1, num = 1;
    bool is_perfect_square = true;
    for (auto& i: arr) {
        cin >> i.first >> i.second;
        d = d * (i.second + 1ll) % mod;
        sum = sum * sigma(i.first, i.second) % mod;
        num = num * poww(i.first, i.second) % mod;
        is_perfect_square &= (i.second % 2 == 0);
    }
    ll product = 1; // prod pi ^ ((d * ki)/2)
    // = num ^ (d/2) for num not ps
    // = sqrt(num) ^ d for ps
    if (is_perfect_square) {
        ll dm = 1;
        num = 1;
        for (auto i: arr) {
            num = num * poww(i.first, i.second/2) % mod;
            dm = dm * (i.second + 1ll) % (mod-1);
        }
        product = poww(num, dm);
    }
    else {
        bool once = false;
        ll dm = 1;
        for (auto i: arr) {
            if (!once && (i.second&1)) {    //doing this cause cant find inv 2 under mod-1 since they aren't coprime
                dm = dm * ((i.second+1ll)/2) % (mod-1);
                once = true;
            }
            else
                dm = dm * (i.second + 1ll) % (mod-1);
        }
        product = poww(num, dm);
    }
    cout << d << " " << sum << " " << product << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}