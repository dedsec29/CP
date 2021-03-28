#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; cin>>n;
    int h[n], nge[n];   //greater or equal
    for (int i=0;i<n;i++) cin>>h[i];
    int ans[n] = {0};
    stack<pair<int,int>> s;
    for (int i=0;i<n;i++) {
        if (s.empty()) {
            s.push({h[i], i});
            continue;
        }
        while (!s.empty() && s.top().first<=h[i]) {
            nge[s.top().second] = i;
            s.pop();
        }
        s.push({h[i], i});
    }
    while (!s.empty()) {
        nge[s.top().second] = -1;
        s.pop();
    }
    bool vis[n] = {false};
    for (int i=0;i<n;i++) {
        if (vis[i])
            continue;
        int c = 0;
        int j = nge[i];
        while (j!=-1 && h[j]==h[i]) {
            c++;
            vis[j] = true;
            j = nge[j];
        }
        j = i;
        while (j!=-1 && h[j]==h[i]) {
            ans[j] = c;
            j = nge[j];
        }
        vis[i] = true;
    }
    for (int i=0;i<n;i++) cout<<ans[i]<<" ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin>>t;
    while (t--) 
        solve();
    return 0;
}