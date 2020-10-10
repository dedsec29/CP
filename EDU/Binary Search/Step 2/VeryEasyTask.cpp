#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll n,x,y;

bool func(ll t) {
    return ((t>=min(x,y)) && ((t/min(x,y) + (t-min(x,y))/max(x,y))>=n));
}

int main() {
    cin>>n>>x>>y;
    ll l=0, r=max(x,y)*n+1ll;
    while (r>l+1) {
        ll mid = (l+r)/2;
        if (func(mid)) r=mid;
        else l=mid;
    }
    cout<<r;
    return 0;
}