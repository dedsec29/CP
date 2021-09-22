#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll const inf = 1e15;
int const siz = 1e5;
vector<pair<int,ll>> adj[siz+1];

void dijkstra(int source,vector<ll>& d) { //O(nlogn + mlogn) = O(mlogn)   (sparse efficient)
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m; cin>>n>>m;
    while (m--) {
        int u,v; ll w; cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }
    vector<ll> d(n+1, inf);
    dijkstra(1, d);
    for (int i = 1; i <= n; i++)
        cout << d[i] << " ";
    return 0;
}