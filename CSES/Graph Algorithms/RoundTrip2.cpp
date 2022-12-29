#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

int const siz = 1e5;
vector<int> adj[siz+1];
bool vis[siz+1];

deque<int> ans;

void dfs(int v,deque<int>& path,set<int>& lookup) {
    vis[v] = true;
    path.push_back(v);
    lookup.insert(v);
    for (int i: adj[v]) {
        if (vis[i]) {
            // cycle detected
            if (ans.empty() && lookup.find(i) != lookup.end()) {
                ans = path;
                ans.push_back(i);
            }
        }
        else 
            dfs(i, path, lookup);
    }
    path.pop_back();
    lookup.erase(v);
}

void solve() {
    int n,m; cin >> n >> m;
    while (m--) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            deque<int> path;
            set<int> lookup;
            dfs(i, path, lookup);
            if (!ans.empty())
                break;
        }
    }
    if (ans.empty()) cout << "IMPOSSIBLE\n";
    else {
        while (!ans.empty() && ans.front() != ans.back())
            ans.pop_front();
        cout << ans.size() << "\n";
        for (int i: ans) cout << i << " ";
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}