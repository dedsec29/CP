#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

// We know what's an s-t cut. I wanna delete min edges and make both sets disjoint
// If I choose min cut, the min cut flow will give me the least number of edges to cut.
// because the capacity of each flow is just 1 (can extend to capacity > 1)
// (can consider it as count in this case? Not exactly, cause an edge might run you into
// a subgraph that ends no where near t. So consider it as flow. Flow never go through that edge)
// (in a way, the flow is giving the imp edges to cut that actually affect the answer)

// How to find the min cut ? Explained in Problems/Flows/Terminology

int const siz = 500;
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
        bool once = false;
        while (v != s) {
            int p = parent[v];
            capacity[p][v] -= new_flow;     // residual capacity
            capacity[v][p] += new_flow;     // reversed edge
            v = p;
        }
    }
    return F;
}

vector<pair<int,int>> minCut(int s,int t,int n) {
    vector<bool> vis(n+1);
    vis[s] = true;
    queue<int> Q;
    Q.push(s);
    set<int> A;     
    A.insert(s);
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int i: adj[v]) {
            if (!vis[i] && capacity[v][i]) {
                vis[i] = true;
                Q.push(i);
                A.insert(i);
            }
        }
    }
    vector<pair<int,int>> ans;
    for (int i: A) {
        for (int j: adj[i]) {
            if (A.find(j) == A.end())
                ans.emplace_back(i,j);
        }
    }
    return ans;
}

void solve() {
    int n,m; cin >> n >> m;
    while (m--) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] += 1;
        capacity[v][u] += 1;  // 2 WAY STREETS
        // capacity of back edge = 0 => no reversed edges yet => now flow to source
    }
    ll F = maxFlow(1,n, n);
    cout << F << "\n";
    vector<pair<int,int>> ans = minCut(1,n, n);
    for (auto i: ans) cout << i.first << " " << i.second << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}