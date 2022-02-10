#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

int const siz = 500;
vector<int> adj[siz+1];
ll capacity[siz+1][siz+1];

ll bfs(int s,int t,vector<int>& parent,int n) {
    // find shortest length Augment Path
    // and return the bottleneck
    fill(parent.begin(), parent.end(), -1); // -1 implies unvisited too
    parent[s] = -2;                         // visited
    queue<pair<int,ll>> Q;                  // second maintains bottleneck so far
    Q.push({s, LLONG_MAX});

    while (!Q.empty()) {
        int v = Q.front().first;
        ll flow = Q.front().second;
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

ll maxFlow(int s,int t,int n) {
    vector<int> parent(n+1, -1);
    ll F = 0;
    while (ll new_flow = bfs(s,t,parent,n)) {
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

void solve() {
    int n,m; cin >> n >> m;
    while (m--) {
        int u,v; ll c; cin >> u >> v >> c;
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += c;        // combine multiple pipes
        // capacity of back edge = 0 => no reversed edges yet => now flow to source
    }
    ll F = maxFlow(1,n, n);
    cout << F << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}