#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

int const siz = 1e5;
vector<int> adj[siz+1], adj_rev[siz+1];
vector<int> order;   // order: list of nodes with descending exit time 
vector<bool> vis;

void dfs1(int v) {
    vis[v] = true;
    for (int i: adj[v]) if (!vis[i]) dfs1(i);
    order.push_back(v);
}

void dfs2(int v) {
    vis[v] = true;
    for (int i: adj_rev[v]) if (!vis[i]) dfs2(i);
}

void solve() {
    int n,m; cin >> n >> m;
    int k = 0, a = -1, b = -1;
    vis.assign(n+1, false);
    while (m--) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }
    // Get list of vertices sorted in descending order of exit time
    for (int i = 1; i <= n; i++) if (!vis[i]) dfs1(i);
    reverse(order.begin(), order.end());
    vis.assign(n+1, false);
    // Find components in source SCC, delete them, get new source Scc.. so on
    for (int i: order) {
        if (!vis[i]) {
            dfs2(i);
            k++;
            if (k == 1)
                a = i;
            else {
                b = i;
                break;
            }
        }
    }
    if (k == 1) cout << "YES";
    else cout << "NO\n" << b << " " << a;
    // b->a, not a->b  (imp)
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}