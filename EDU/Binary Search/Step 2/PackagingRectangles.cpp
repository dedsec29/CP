#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll w,h,n;

bool func(ll x) {//if we can accomodate more rectangles then n, return good
    return (((x/h)*(x/w))>=n);  //true for good
}

int main() {
    cin>>w>>h>>n;
    ll l=0, r=1;
    while (!func(r)) 
        r<<=1ll;
    while (r>l+1) {
        ll mid = (l+r)/2;
        if (func(mid)) r=mid;
        else l=mid;
    }
    cout<<r;
    return 0;
}