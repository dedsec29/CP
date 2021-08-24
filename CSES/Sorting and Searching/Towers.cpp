#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; cin>>n;
    vector<int> v;
    for (int i=0;i<n;i++) {
        int r; cin>>r;
        int pos = upper_bound(v.begin(),v.end(),r) - v.begin();
        if (pos == v.size())
            v.push_back(r);
        else
            v[pos] = r;
    }
    cout << v.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}