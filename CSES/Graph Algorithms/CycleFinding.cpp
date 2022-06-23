#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

// Use knowledge from Bellman Ford
// How to handle disconnected graph? 
// We can have a dummy node, connect it to every other node, have the weights 0
// Now it is again SSSP problem from the dummy node
// We don't explicitly need to add these edges. Just make d[i] = 0
// Now number of phases to detect cycle = n+1 (because of the dummy node)
// d[i] = 0 => essentially we performed the first phase directly

struct edge {
    int a,b;
    ll cost;
};

ll const inf = 1e17;     // n*m*maxW

vector<int> BellmanFord(vector<edge>& e,int n,vector<ll>& d) {
    vector<int> path;
    int v = -1;
    vector<int> parent(n+1, -1);
    for (int phase = 2; phase <= n+1; phase++) {
        v = -1;
        for (auto& i: e) {
            if (d[i.a] < inf && d[i.b] > d[i.a] + i.cost) {
                d[i.b] = d[i.a] + i.cost;
                v = i.b;
                parent[i.b] = i.a;
            }
        }
    }
    if (v == -1) return path;
    // We want node that is present in cycle, then only we can find the cycle
    // How to garuantee that the node we found in nth phase was part of a cycle?
    // (We need to think about this cause -ve cycle can propogate to nodes not part of any cycle too)
    // If we trace back the node n times, we are sure to reach the cause (node in a cycle)
    for (int i = 0; i < n; i++) 
        v = parent[v];
    int x = v;
    while (true) {
        path.push_back(x);
        x = parent[x];
        if (x == v) {
            path.push_back(x);
            break;
        }
    }
    reverse(path.begin(), path.end());
    return path;
}

void solve() {
    int n,m; cin >> n >> m;
    vector<edge> e(m);
    for (int i = 0; i < m; i++) {
        int u,v; ll w; cin >> u >> v >> w;
        e[i].a = u, e[i].b = v, e[i].cost = w;
    }
    // phase 1 complete
    vector<ll> d(n+1);
    vector<int> path = BellmanFord(e, n, d);
    if (path.empty()) {
        cout << "NO";
        return;
    }
    cout << "YES\n";
    for (int i: path) cout << i << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}