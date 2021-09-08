#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll poww(ll a,ll b,ll mod) {
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

ll solve(ll a,ll b,ll c) {
    ll mod = 1e9+7;
    //Fermat's lil theorem: (a^b)%mod = (a ^ (b % phi(m)) )%mod 
    //calc b^c under phi(m) = m-1
    return poww(a, poww(b,c,mod-1) % (mod-1), mod);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin>>t;
    while (t--) {
        int a,b,c; cin>>a>>b>>c;
        cout << solve(a,b,c) << "\n";
    }
    return 0;
}