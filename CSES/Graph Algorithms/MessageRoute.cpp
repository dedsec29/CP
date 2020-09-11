#include <bits/stdc++.h>
using namespace std;

int const siz = 1e5;

bitset<siz+1> vis;
vector<int> adj[siz+1];
int dist[siz+1], parent[siz+1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m; cin>>n>>m;
    while (m--) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i=2;i<=n;i++) dist[i]=-1;
    queue<int> Q; dist[1]=0;
    Q.push(1); vis[1]=1;
    while (!Q.empty()) {
        int a = Q.front();
        Q.pop();
        if (a==n) break;
        for (int i: adj[a]) {
            if (vis[i]==0) {
                Q.push(i);
                parent[i]=a;
                dist[i]=dist[a]+1;
                vis[i]=1;
            }
        }
    }
    if (dist[n]==-1) cout<<"IMPOSSIBLE";
    else {
        cout<<dist[n]+1<<"\n";
        stack<int> s;
        int x = n;
        while (x!=1) {
            s.push(x);
            x=parent[x];
        }
        s.push(1);
        while (!s.empty()) cout<<s.top()<<" ", s.pop();
    }
    return 0;
}