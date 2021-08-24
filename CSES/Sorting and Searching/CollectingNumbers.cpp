#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; cin>>n;
    vector<int> pos(n+1);
    for (int i=1;i<=n;i++) {
        int r; cin>>r;
        pos[r] = i;
    }
    int ans = 1;
    for (int i=2;i<=n;i++)
        ans += (pos[i-1] > pos[i]);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}