#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; ll k; cin>>n>>k;
    vector<ll> arr(n);
    for (ll& i: arr) cin>>i;
    map<ll,int> mp;
    ll ans = 0;
    for (int l=0,r=0;r<n;r++) {
        mp[arr[r]]++;
        while (mp.rbegin()->first - mp.begin()->first > k) {
            mp[arr[l]]--;
            if (mp[arr[l]]==0)
                mp.erase(arr[l]);
            l++;
        }
        ans += (ll) r-l+1;
    }
    cout<<ans;
    // why can we apply 2 pointer here?
    // the max right to curr is increasing, and if diff exceeds k,
    // no matter how right you go, other elements that might b<=a+k never come cause max is > b
    // same logic for l
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}