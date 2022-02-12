#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

// This is just Maximum Bipartite match (weight = 1)
// Why? Cause we need maximum number of paths sharing no edges (s to t)

int const siz = 1001;   // N + M + 1    (Important)
vector<int> adj[siz+1];
int capacity[siz+1][siz+1];

int bfs(int s,int t,vector<int>& parent,int n) {
    // find shortest length Augment Path
    // and return the bottleneck
    fill(parent.begin(), parent.end(), -1); // -1 implies unvisited too
    parent[s] = -2;                         // visited
    queue<pair<int,int>> Q;                  // second maintains bottleneck so far
    Q.push({s, INT_MAX});

    while (!Q.empty()) {
        int v = Q.front().first;
        int flow = Q.front().second;
        Q.pop();
        if (v == t)
            return flow;
        for (int i: adj[v]) {
            if (parent[i] == -1 && capacity[v][i]) {    // residual capacity > 0
                flow = min(flow, capacity[v][i]);
                parent[i] = v;
                Q.push({i, flow});
            }
        }
    }
    return 0;
}

int maxFlow(int s,int t,int n) {
    vector<int> parent(n+1, -1);
    int F = 0;
    while (int new_flow = bfs(s,t,parent,n)) {
        F += new_flow;
        // augment the shortest path found
        int v = t;
        while (v != s) {
            int p = parent[v];
            capacity[p][v] -= new_flow;     // residual capacity
            capacity[v][p] += new_flow;     // reversed edge
            v = p;
        } 
    }
    return F;
}

vector<pair<int,int>> matched_edges(int n,int m) {
    // returns matching between n and m  (m returned as v-n)
    vector<pair<int,int>> ans;
    for (int i = 1; i <= n; i++) {
        for (int j = n+1; j <= n+m; j++) {
            if (capacity[j][i])      
                ans.emplace_back(i,j-n);
        }
    }
    return ans;
}

void solve() {
    int n,m; cin >> n >> m;
    // encode vetices in set B as n+1,n+2,..,n+
    // s = 0 and t = n+m+1
    int k; cin >> k;
    while (k--) {
        int u,v; cin >> u >> v;
        v = n+v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        // adding 2 way edges is necessary (for correct traversal of residue graph)
        // If input is directed, only update capacity of u->v, else both
        capacity[u][v] += 1;
    }
    for (int i: A) {
        adj[0].push_back(i);
        capacity[0][i] += 1;
    }
    for (int i: B) {
        adj[i].push_back(n+m+1);
        capacity[i][n+m+1] += 1;
    }
    cout << maxFlow(0,n+m+1, n+m+1) << "\n";
    vector<pair<int,int>> ans = matched_edges(n,m);
    for (auto i: ans) cout << i.first << " " << i.second << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}