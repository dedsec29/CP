#include <bits/stdc++.h>
using namespace std;

int const siz = 1e5;

bitset<siz+1> vis;
vector<int> adj[siz+1];

void dfs(int v) {
    vis[v]=1;
    for (int i: adj[v]) {
        if (vis[i]==0) dfs(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m; cin>>n>>m;
    while (m--) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int cc=0;
    vector<int> v;
    for (int i=1;i<=n;i++) {
        if (vis[i]==0) {
            dfs(i);
            cc++; v.push_back(i);
        }
    }
    cout<<cc-1<<"\n";
    for (int i=0;i<v.size()-1;i++) cout<<v[i]<<" "<<v[i+1]<<"\n";
    return 0;
}