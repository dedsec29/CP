#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

// https://cp-algorithms.web.app/graph/strongly-connected-components.html
// https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/tutorial/
// O(V^3) exists too. For i in V, for j in V, i and j reachable each other? Then same SCC

// Imagine condensing all SCCs into a Single node. C and C' are nodes of 2 such sccs.
// Then if C -> C' edge exists, exit time of C > exit time C'
// So in condensed graph's DAG, one with most exit time is like the source
// Reverse edges and do DFS on root, we will visit only that source component
// (since C -> C' also got reversed, only the SCC gets visited)
// Now delete these nodes, we have new source comp. Apply same logic 

int const siz = 1e5;
vector<int> adj[siz+1], adj_rev[siz+1];
vector<int> order, component;   // order: list of nodes with descending exit time 
vector<bool> vis;

void dfs1(int v) {
    vis[v] = true;
    for (int i: adj[v]) if (!vis[i]) dfs1(i);
    order.push_back(v);
}

void dfs2(int v) {
    vis[v] = true;
    component.push_back(v);
    for (int i: adj_rev[v]) if (!vis[i]) dfs2(i);
}

void solve() {
    int n,m; cin >> n >> m;
    vector<int> ans(n+1);
    int k = 0;
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
            for (int j: component) ans[j] = k;
            component.clear();
        }
    }
    cout << k << "\n";
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}