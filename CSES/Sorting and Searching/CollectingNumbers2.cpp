#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n,m; cin>>n>>m;
    vector<int> arr(n+1), pos(n+1);
    for (int i=1;i<=n;i++) {
        cin>>arr[i];
        pos[arr[i]] = i;
    }
    int ans = 1;
    for (int i=2;i<=n;i++)
        ans += (pos[i-1] > pos[i]);
    while (m--) {
        int a,b; cin>>a>>b;
        if (a>b) swap(a,b);
        if (arr[a]<n && a<pos[arr[a]+1] && pos[arr[a]+1]<b) ans++;
        if (1<arr[b] && a<pos[arr[b]-1] && pos[arr[b]-1]<b) ans++;
        if (1<arr[a] && a<pos[arr[a]-1] && pos[arr[a]-1]<b) ans--;
        if (arr[b]<n && a<pos[arr[b]+1] && pos[arr[b]+1]<b) ans--;
        if (arr[a] == arr[b]-1) ans++;
        if (arr[a] == arr[b]+1) ans--;
        cout << ans << "\n";
        swap(pos[arr[a]],pos[arr[b]]);
        swap(arr[a],arr[b]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}