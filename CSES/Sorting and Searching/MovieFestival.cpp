#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

bool intersects(pair<int,int>& a,pair<int,int>& b) {
    return !((a.second <= b.first) || (b.second <= a.first));
}

void solve() {
    int n; cin>>n;
    vector<pair<int,int>> arr(n);
    for (int i=0;i<n;i++) cin>>arr[i].first>>arr[i].second;
    sort(arr.begin(), arr.end(), [](pair<int,int>& a,pair<int,int>& b) {return a.second < b.second;});
    int ans = 1;
    pair<int,int> curr = arr[0];
    for (int i=1;i<n;i++) {
        if (!intersects(arr[i], curr)) {
            curr = arr[i];
            ans++;
        }
    }
    cout<<ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}