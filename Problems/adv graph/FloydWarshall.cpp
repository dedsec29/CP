#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll const inf = 1e14;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m,q; cin>>n>>m>>q;
    vector<vector<ll>> d(n, vector<ll>(n, inf));
    for (int i=0;i<n;i++) d[i][i]=0;
    while (m--) {
        int u,v; ll w; cin>>u>>v>>w; u--,v--;
        d[u][v] = min(w, d[u][v]);
        d[v][u] = min(w, d[v][u]);
    }
    for (int k=0;k<n;k++) 
        for (int i=0;i<n;i++) 
            for (int j=0;j<n;j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    while (q--) {
        int a,b; cin>>a>>b; a--, b--;
        ll ans = (d[a][b]<inf)?d[a][b]:-1;
        cout<<ans<<"\n";
    }
    return 0;
}
