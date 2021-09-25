#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll const inf = 1e15;
int const siz = 1e5;
vector<pair<int,ll>> adj[siz+1];

void dijkstra(int source,vector<ll>& d,vector<int>& parent) { 
    set<pair<ll,int>> s;
    d[source] = 0;
    s.insert({0, source});
    while (!s.empty()) {
        int v = s.begin()->second;  //choosing min unmarked v
        s.erase(s.begin());
        // performing relaxation
        for (auto i: adj[v]) {
            int to = i.first;
            ll wt = i.second;
            if (d[to] >= inf || d[v] + wt < d[to]) {
                s.erase({d[to], to});
                d[to] = d[v] + wt;
                parent[to] = v;
                s.insert({d[to], to});
            }
        }
    }
}

void solve() {
    int n,m; cin>>n>>m;
    while (m--) {
        int u,v; ll w; cin>>u>>v>>w;
        if (u == v)
            continue;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    vector<ll> d(n+1, inf);
    vector<int> parent(n+1, -1);
    dijkstra(1, d, parent);
    if (d[n] >= inf) {
        cout << "-1\n";
        return;
    }
    vector<int> path;
    int x = n;
    while (x != -1) {
        path.push_back(x);
        x = parent[x];
    }
    reverse(path.begin(), path.end());
    for (int i: path) cout << i << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}