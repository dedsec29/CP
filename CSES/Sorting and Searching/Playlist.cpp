#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; cin>>n;
    vector<int> arr(n);
    for (int& i: arr) cin>>i;
    set<int> s;
    int ans = 0;
    for (int l=0,r=0;r<n;r++) {
        while (s.find(arr[r]) != s.end()) 
            s.erase(arr[l++]);
        s.insert(arr[r]);
        ans = max(r-l+1,ans);
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}