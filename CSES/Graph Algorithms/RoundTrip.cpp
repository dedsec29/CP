#include <bits/stdc++.h>
using namespace std;

int const siz = 1e5;
vector<int> adj[siz+1];
bool vis[siz+1];
int parent[siz+1];
int start,eend;

void dfs (int v,int p) {
    vis[v]=true;
    for (int i: adj[v]) {
        if (i==p) continue;
        if (vis[i]) {
            if (start==0) {
                start = i, eend = v;
            }
        }
        else {
            parent[i] = v;
            dfs(i, v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m; cin>>n>>m;
    while (m--) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i=1;i<=n;i++) {
        if (start!=0) break;
        if (!vis[i]) dfs(i,0);
    }
    if (start==0) cout<<"IMPOSSIBLE";
    else {
        int x = eend;
        vector<int> ans;
        while (x!=start) {
            ans.push_back(x);
            x = parent[x];
        }
        ans.push_back(start);
        ans.push_back(eend);
        cout<<ans.size()<<"\n";
        for (int i: ans) cout<<i<<" ";
    }
    return 0;
}