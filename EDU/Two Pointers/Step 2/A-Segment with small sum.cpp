#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; cin>>n;
    ll s; cin>>s;
    vector<ll> arr(n);
    for (int i=0;i<n;i++) cin>>arr[i];
    ll curr = 0;
    int ans = 0;
    for (int l=0,r=0;r<n;r++) {
        curr += arr[r];
        while (curr > s) {
            curr -= arr[l];
            l++;
        }
        ans = max(ans, r-l+1);
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}