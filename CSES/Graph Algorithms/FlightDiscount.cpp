#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll const inf = 1e15;
int const siz = 4e5;
vector<pair<int,ll>> adj[siz+1];

//2 copies of graph, alternate realities when discount used
//other solutions exist (check USACO)

void dijkstra(int source,vector<ll>& d) { 
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
    }
    for (int i = 1; i <= n; i++) {
        vector<pair<int,ll>> to_insert;
        for (auto j: adj[i]) {
            adj[i+n].push_back({j.first+n, j.second});
            to_insert.push_back({j.first+n, j.second/2});
        }
        for (auto j: to_insert)
            adj[i].emplace_back(j);
        sort(adj[i].begin(), adj[i].end()); //cause multiple edges
    }
    vector<ll> d(2*n+1, inf);
    dijkstra(1, d);
    cout << min(d[n], d[2*n]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}