#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize "trapv"
#define ll long long

bool func(double t,int n,ll x[],ll v[]) {
    double L = -numeric_limits<double>::infinity();
    double R = numeric_limits<double>::infinity();
    for (int i=0;i<n;i++) {
        L = max(L, -t*v[i]+x[i]);
        R = min(R, t*v[i]+x[i]);
    } 
    return (R-L)>=(1e-300);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin>>n;
    ll x[n], v[n];
    for (int i=0;i<n;i++) cin>>x[i]>>v[i];
    double L = -1, R = 1e9+5;
    for (int i=1;i<=100;i++) {
        double mid = (L+R)/2.0;
        if (func(mid,n,x,v)) 
            R = mid;
        else
            L = mid;
    }
    cout<<fixed<<setprecision(6)<<R;
    return 0;
}