#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

// up[i][j] = i's 2^j th ancestor
// up[i][j] = up[ up[i][j-1] ][j-1]

class BinaryLifting {
public:
    int n,ub;
    vector<int> depth;
    vector<vector<int>> up, adj;

    BinaryLifting(int root,vector<vector<int>>& adj_) {
        n = adj_.size()-1;   // 1 based
        adj = adj_;
        ub = __lg(n);
        depth.resize(n+1);
        up = vector<vector<int>>(n+1, vector<int>(ub+1, -1));
        dfs(root, -1, 0);
    }

    void dfs(int v,int p,int d) {
        depth[v] = d;
        up[v][0] = p;
        for (int i = 1; i <= ub; i++) {
            if (up[v][i-1] == -1)
                up[v][i] = -1;
            else
                up[v][i] = up[ up[v][i-1] ][i-1];
        }
        for (int i: adj[v]) {
            if (i == p) continue;
            dfs(i,v,d+1);
        }
    }

    int kthAncestor(int v,int k) {
        // k as sum of powers of 2 (binary)
        for (int i = 0; k != 0 && i <= ub; i++, k >>= 1) {
            if (k&1) {
                if (up[v][i] == -1)
                    return -1;
                v = up[v][i];
            }
        }
        if (k != 0)
            return -1;
        return v;
    }

    int lca(int u,int v) {
        if (depth[u] < depth[v])
            swap(u,v);
        int k = depth[u] - depth[v];
        u = kthAncestor(u, k);
        if (u == v)
            return u;
        // binary search on how much above is still an ancestor (get as close as possible to lca)
        for (int i = ub; i >= 0; i--) {
            if (up[u][i] == -1)
                continue;
            if (up[u][i] != up[v][i]) 
                u = up[u][i], v = up[v][i];
        }
        return up[u][0];
    }
};

void solve() {
    int n,q; cin >> n >> q;
    vector<vector<int>> adj(n+1);
    for (int i = 2; i <= n; i++) {
        int p; cin >> p;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }
    BinaryLifting X(1, adj);
    while (q--) {
        int u,v; cin >> u >> v;
        cout << X.lca(u, v) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}