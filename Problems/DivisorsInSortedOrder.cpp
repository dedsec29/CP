#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long
//https://codeforces.com/problemset/problem/762/A
void solve() {
    ll n,k; cin>>n>>k;
    ll i=1, cnt = 0;
    for (;i*i<=n;i++) {
        if (n%i==0) {
            cnt++;
            //cout<<cnt<<" "<<(i)<<"\n";
            if (cnt==k) {
                cout<<i<<"\n";
                return;
            }
        }
    }
    i--;
    if (i*i==n) i--;
    for (;i>=1;i--) {
        if (n%i==0) {
            cnt++;
            //cout<<cnt<<" "<<(n/i)<<"\n";
            if (cnt==k) {
                cout<<(n/i)<<"\n";
                return;
            }
        }
    }
    cout<<"-1\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}