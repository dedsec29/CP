#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize "trapv"
#define ll long long
 
vector<ll> make_subsets(vector<ll> arr) {
    int n = arr.size();
    int ub = 1<<n;
    vector<ll> ans;
    // empty subset in both A and B?
    for (int i = 1; i < ub; i++) {
        ll sum = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1<<j))
                sum += arr[j];
        }
        ans.push_back(sum);
    }
    return ans;
}
 
void solve() {
    int n; cin >> n;
    ll x; cin >> x;
    vector<ll> arr(n);
    for (auto& i: arr) cin >> i;
    // A has n/2 substets, B has the other
    vector<ll> A = make_subsets(vector<ll>(arr.begin(), arr.begin() + n/2));
    vector<ll> B = make_subsets(vector<ll>(arr.begin() + n/2, arr.end()));
    // either a subset in A, or combo of subsets from A and B
    // (B and A itself contain subsets of 1 or more elements)
    // dont need to consider combos in A cause they already exist in A bruh
    // now do 2 ptr / bs / hashmap stuff
    // map is slow, TLEs
    ll ans = 0;
    // initialize answer with ans for only B
    for (auto i: B) if (i == x) ans++;
    sort(B.begin(), B.end());
    for (auto val: A) {
        if (val == x) {
            ans++;
            continue;
        }
        ans += upper_bound(B.begin(),B.end(),x-val) - lower_bound(B.begin(),B.end(),x-val);
    }
    cout << ans << "\n";
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}