#include <bits/stdc++.h>
using namespace std;

int const siz = 1e5;
vector<int> adj[siz+1];
int colour[siz+1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m; cin>>n>>m;
    while (m--) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    bool imp = false;
    for (int a=1;a<=n;a++) {
        if (colour[a]) continue;
        queue<int> Q;
        Q.push(a); colour[a]=1;
        while (!Q.empty()) {
            int v = Q.front();
            Q.pop();
            int assign = (colour[v]==1)?2:1;
            for (int i: adj[v]) {
                if (colour[i]==0) {
                    Q.push(i);
                    colour[i]=assign;
                }
                else {
                    if (colour[i]!=assign) {
                        imp = true;
                        goto here;
                    }
                }
            }
        }
    }
    here:
    if (imp) cout<<"IMPOSSIBLE";
    else for (int i=1;i<=n;i++) cout<<colour[i]<<" ";
    return 0;
}