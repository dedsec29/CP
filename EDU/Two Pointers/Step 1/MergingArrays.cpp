#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n,m; cin>>n>>m;
    vector<int> a(n), b(m), c(n+m);
    for (int &i: a) cin>>i;
    for (int &i: b) cin>>i;
    int l,r,k; l=r=k=0;
    while (l<n || r<m) {
        if (r==m || (l<n && (a[l]<=b[r])))
            c[k++] = a[l++];
        else
            c[k++] = b[r++];
    }
    for (int i: c) cout<<i<<" ";
    cout<<"\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}