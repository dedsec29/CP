#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll check(vector<ll>& arr,ll x,int n,int k) {
    int cnt = 0;
    ll mx = 0;
    for (int i=1;i<=n;i++) {
        ll curr = 0;
        int j = i;
        if (arr[i] > x)
            return -1;
        while (j <= n && curr + arr[j] <= x)
            curr += arr[j++];
        mx = max(mx, curr);
        cnt++;
        i = j-1;
    }
    if (cnt <= k) return mx;
    return -1;
}

void solve() {
    int n,k; cin>>n>>k;
    ll l = 0, r = 0;
    vector<ll> arr(n+1);
    for (int i=1;i<=n;i++) {
        cin>>arr[i];
        r += arr[i];
    }
    r++;
    ll ans = 0;
    while (r-l>1) {
        ll mid = (l+r)>>1;
        ll calc = check(arr, mid, n, k);
        if (calc == -1)
            l = mid;
        else {
            r = mid;
            ans = calc;
        }
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}