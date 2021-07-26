#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    int n,k; cin>>n>>k;
    map<int,int> mp;
    vector<int> arr(n);
    for (int &i: arr) cin>>i;
    ll ans = 0;
    for (int l=0,r=0;r<n;r++) {
        mp[arr[r]]++;
        while (mp.size() > k) {
            mp[arr[l]]--;
            if (mp[arr[l]]==0)
                mp.erase(arr[l]);
            l++;
        }
        ans += (ll) r-l+1;
    }
    cout<<ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}