#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n,m; cin>>n>>m;
    vector<int> a(n), b(m);
    for (int &i: a) cin>>i;
    for (int &i: b) cin>>i;
    int l=0,r=0;
    ll ans = 0;
    while (l<n && r<m) {
        if (a[l]==b[r]) {
            ll c1 = 0, c2 = 0;
            while (r<m && b[r]==a[l]) {
                r++;
                c1++;
            }
            while (l<n && b[r-1]==a[l]) {
                l++;
                c2++;
            }
            ans += c1*c2;
        }
        else if (a[l]<b[r])
            l++;
        else
            r++;
    }
    cout<<ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}