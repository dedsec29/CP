#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma")

bool good(pair<int,int>& a,pair<int,int>& b) {
    set<int> s;
    s.insert(a.first);
    s.insert(a.second);
    s.insert(b.first);
    s.insert(b.second);
    return (s.size() == 4);
}

void solve() {
    int n; ll x; cin>>n>>x;
    vector<ll> arr(n+1);
    for (int i=1;i<=n;i++) cin>>arr[i];
    vector<pair<ll, pair<int,int>>> doublet_sums;
    doublet_sums.reserve((n*n)/2);
    for (int i=1;i<=n;i++) {
        for (int j=i+1;j<=n;j++) 
            doublet_sums.push_back({arr[i]+arr[j], {i,j}});
    }
    sort(doublet_sums.begin(), doublet_sums.end());
    int len = doublet_sums.size();
    int l = 0, r = len-1;
    while (l < r) {
        if (good(doublet_sums[l].second,doublet_sums[r].second) && doublet_sums[l].first + doublet_sums[r].first == x) {
            cout << doublet_sums[l].second.first << " " << doublet_sums[l].second.second << " " << doublet_sums[r].second.first << " " << doublet_sums[r].second.second;
            return;
        }
        else if (doublet_sums[l].first + doublet_sums[r].first < x)
            l++;
        else
            r--;
    }
    cout << "IMPOSSIBLE";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}