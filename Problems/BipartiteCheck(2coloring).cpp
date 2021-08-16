#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

//https://codeforces.com/problemset/problem/1093/D
//bipartite doesnt always mean n/2 nodes of each col, can differ

ll const mod = 998244353;
int const siz = 3e5+5;
ll p2[siz+1];
vector<int> adj[siz+1];
int colour[siz+1];

bool check_bipartite(int v,int c,vector<int>& freq) {
    colour[v] = c;
    freq[c]++;
    bool yes = true;
    for (int i: adj[v]) {
        if (colour[i] == c) 
            yes = false;
        else {
            if (colour[i] == -1)
                yes &= check_bipartite(i, c^1, freq);
        }
    }
    return yes;
}

void solve() {
    int n,m; cin>>n>>m;
    for (int i=1;i<=n;i++) {
        colour[i] = -1;
        adj[i].clear();
    }
    while (m--) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ll ans = 1;
    for (int i=1;i<=n;i++) {
        if (colour[i] == -1) {
            vector<int> freq(2);
            if (!check_bipartite(i,0,freq)) {
                cout<<"0\n";
                return;
            }
            ll x = (p2[freq[1]] + p2[freq[0]])%mod;
            ans = (ans * x)%mod;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    p2[0] = 1;
    for (int i=1;i<=siz;i++)
        p2[i] = (p2[i-1] * 2ll)%mod;
    int t; cin>>t;
    while (t--) 
        solve();
    return 0;
}