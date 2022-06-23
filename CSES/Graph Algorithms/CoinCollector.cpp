#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

int const siz = 1e5;
vector<int> adj[siz+1], adj_rev[siz+1], condensed[siz+1];
vector<int> order, component;   // order: list of nodes with descending exit time 
int root[siz+1];   // ith node is represented by which node in condensed graph?
vector<bool> vis;
ll A[siz+1];

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

ll maxCostPathDAG(int n) {
    vector<ll> dp(n+1);
    queue<int> Q;
    vector<int> indegree(n+1);
    for (int i = 1; i <= n; i++) {
        for (int j: condensed[i])
            indegree[j]++;
    }
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            Q.push(i);
            dp[i] = A[i];
        }
    }
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int i: condensed[v]) {
            dp[i] = max(dp[i], dp[v] + A[i]);
            indegree[i]--;
            if (indegree[i] == 0)
                Q.push(i);
        }
    }
    return *max_element(dp.begin(), dp.end());
}

void solve() {
    int n,m; cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> A[i];
    vis.assign(n+1, false);
    while (m--) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) if (!vis[i]) dfs1(i);
    reverse(order.begin(), order.end());
    vis.assign(n+1, false);
    // Find components in source SCC
    for (int i: order) {
        if (!vis[i]) {
            dfs2(i);
            int representative = component[0];
            ll sum = 0;
            for (int j: component) {
                root[j] = representative;
                sum += A[j];
            }
            A[representative] = sum;
            component.clear();
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j: adj[i]) {
            if (root[j] != root[i])
                condensed[root[i]].push_back(root[j]);
        }
    }

    cout << maxCostPathDAG(n);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}