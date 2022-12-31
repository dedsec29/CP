#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define int long long

int const inf = 1e15;
int const siz = 1e5;
int const mod = 1e9+7;
vector<pair<int,int>> adj[siz+1];

void dijkstra(int n) { //O(nlogn + mlogn) = O(mlogn)   (sparse efficient)
    vector<int> d(n+1, inf), ways(n+1), mn(n+1, 2*n), mx(n+1);
    d[1] = mx[1] = mn[1] = 0;
    ways[1] = 1;

    set<pair<int,int>> s;
    s.insert({0, 1});
    while (!s.empty()) {
        int v = s.begin()->second;  //choosing min unmarked v
        s.erase(s.begin());
        // performing relaxation
        for (auto i: adj[v]) {
            int to = i.first;
            int wt = i.second;
            if (d[to] == inf || d[v] + wt < d[to]) {
                s.erase({d[to], to});
                
                d[to] = d[v] + wt;
                ways[to] = ways[v];
                mx[to] = mx[v] + 1;
                mn[to] = mn[v] + 1;

                s.insert({d[to], to});
            }
            else if (d[v] + wt == d[to]) {
                ways[to] = (ways[to] + ways[v]) % mod;
                mx[to] = max(mx[to], mx[v] + 1);
                mn[to] = min(mn[to], mn[v] + 1);
            }
        }
    }
    cout << d[n] << " " << ways[n] << " " << mn[n] << " " << mx[n] << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m; cin>>n>>m;
    while (m--) {
        int u,v, w; cin>>u>>v>>w;
        adj[u].push_back({v,w});
    }
    dijkstra(n);
    return 0;
}