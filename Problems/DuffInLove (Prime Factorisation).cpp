#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize "trapv"
#define ll long long

int main() {
    ll n; cin>>n;
    ll f=1;
    if (n%2==0) {
        f*=2;
        while (n%2==0)
            n>>=1;
    }
    for (ll i=3;i*i<=n;i+=2) {
        if (n%i==0) {
            f*=i;
            while (n%i==0)
                n = n/i;
        }
    }
    if (n>2) f*=n;
    cout<<f;
    return 0;
}