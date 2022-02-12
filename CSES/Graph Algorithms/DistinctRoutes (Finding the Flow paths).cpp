#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

int const siz = 500; 
vector<int> adj[siz+1];
int capacity[siz+1][siz+1];
int cool[siz+1][siz+1];     // cool to traverse edge (undirected)
// Idea is to construct answer by stitching augmented paths (removing critical edges)
// (Algorithms Live)

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
            cool[min(p,v)][max(p,v)] ^= 1;
            capacity[p][v] -= new_flow;     // residual capacity
            capacity[v][p] += new_flow;     // reversed edge
            v = p;
        }
    }
    return F;
}

vector<vector<int>> find_paths(int s,int t,int n) {
    vector<vector<int>> paths;
    for (int i: adj[s]) {
        if (cool[min(s,i)][max(s,i)]) {
            vector<int> v = {s,i};
            cool[min(s,i)][max(s,i)] = 0;
            int curr = i, par = s;
            while (curr != t) {
                for (int j: adj[curr]) {
                    if (j == par) continue;
                    if (cool[min(curr,j)][max(curr,j)]) {
                        cool[min(curr,j)][max(curr,j)] = 0;
                        v.push_back(j);
                        par = curr;
                        curr = j;
                        break;
                    }
                }
            }
            paths.emplace_back(v);
        }
    }
    return paths;
}

void solve() {
    int n,m; cin >> n >> m;
    while (m--) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        // adding 2 way edges is necessary (for correct traversal of residue graph)
        // If input is directed, only update capacity of u->v, else both
        capacity[u][v] += 1;
    }
    
    int F = maxFlow(1,n,n);
    cout << F << "\n";
    vector<vector<int>> paths = find_paths(1,n,n);
    for (auto i: paths) {
        cout << i.size() << "\n";
        for (auto j: i) cout << j << " ";
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}