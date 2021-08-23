#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; cin>>n;
    vector<ll> arr(n);
    for (ll& i: arr) cin>>i;
    sort(arr.begin(), arr.end());
    ll lim = 0;
    for (int i=0;i<n;i++) {
        if (arr[i]-lim > 1)
            break;
        lim += arr[i];
    }   
    cout << lim+1ll;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}