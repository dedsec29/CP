#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

//https://math.stackexchange.com/questions/113270/the-median-minimizes-the-sum-of-absolute-deviations-the-ell-1-norm

void solve() {
    int n; cin>>n;
    vector<ll> arr(n);
    for (ll& i: arr) cin>>i;
    ll ans = 0;
    sort(arr.begin(), arr.end());
    ll x = arr[n/2];
    for (int i=0;i<n;i++)
        ans += abs(x-arr[i]);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}