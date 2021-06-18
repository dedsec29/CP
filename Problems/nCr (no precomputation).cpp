#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize "trapv"
#define ll long long

ll const mod = 1e9+7;

ll poww(ll A,ll N) {
    ll temp;
    if (N==0)
        return 1;
    temp=poww(A,N/2);
    if (N&1)
        return (A*((temp*temp)%mod))%mod;
    else
        return (temp*temp)%mod;
}

ll nCr(ll n,ll r) {
    ll mn = min(n-r,r);
    ll num = 1, den=1;
    for (ll i=0;i<mn;i++)
        num = (num * (n-i))%mod;
    for (ll i=1;i<=mn;i++)
        den = (den * i)%mod;
    return (num * poww(den, mod-2))%mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n,a,b; cin>>n>>a>>b;
    ll pa = nCr(n,a);
    ll pb = nCr(n,b);
    ll p2 = ((poww(2, n) - 1ll)%mod + mod)%mod;
    ll x = (pa+pb)%mod;
    ll ans = ((p2-x)%mod + mod)%mod;
    cout<<ans<<"\n";
    return 0;
}