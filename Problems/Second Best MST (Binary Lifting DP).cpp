#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

// https://cp-algorithms.web.app/graph/second_best_mst.html#implementation
// https://codeforces.com/blog/entry/22325

struct edge {
    int u,v,w,id;
};

map<pair<int,int>, edge> mp;

int getWeight(int v,int p) {
    if (p == -1)
        return 0;     // identity element
    if (v > p)
        swap(v, p);
    return mp[{v,p}].w;
}

class BinaryLifting {
public:
    int n,ub;
    vector<int> depth;
    vector<vector<int>> up, adj, dp;

    BinaryLifting(int root,vector<vector<int>>& adj_) {
        n = adj_.size()-1;   // 1 based
        adj = adj_;
        ub = __lg(n);
        depth.resize(n+1);
        up = vector<vector<int>>(n+1, vector<int>(ub+1, -1));
        dp = vector<vector<int>>(n+1, vector<int>(ub+1));
        dfs(root, -1, 0);
    }

    void dfs(int v,int p,int d) {
        depth[v] = d;
        up[v][0] = p;
        dp[v][0] = getWeight(v, p);
        for (int i = 1; i <= ub; i++) {
            if (up[v][i-1] == -1) {
                up[v][i] = -1;
                dp[v][i] = 0;
            }
            else {
                up[v][i] = up[ up[v][i-1] ][i-1];
                dp[v][i] = max(dp[v][i-1], dp[ up[v][i-1] ][i-1]);
            }
        }
        for (int i: adj[v]) {
            if (i == p) continue;
            dfs(i,v,d+1);
        }
    }

    int kthAncestor(int v,int k,int& ans) {
        // k as sum of powers of 2 (binary)
        for (int i = 0; k != 0 && i <= ub; i++, k >>= 1) {
            if (k&1) {
                if (up[v][i] == -1)
                    return -1;
                ans = max(ans, dp[v][i]);
                v = up[v][i];
            }
        }
        if (k != 0)
            return -1;
        return v;
    }

    int lca(int u,int v,int& ans) {
        ans = 0;
        if (depth[u] < depth[v])
            swap(u,v);
        int k = depth[u] - depth[v];
        u = kthAncestor(u, k, ans);
        if (u == v)
            return u;
        // binary search on how much above is still an ancestor (get as close as possible to lca)
        for (int i = ub; i >= 0; i--) {
            if (up[u][i] == -1)
                continue;
            if (up[u][i] != up[v][i]) {
                ans = max({ans, dp[u][i], dp[v][i]});
                u = up[u][i], v = up[v][i];
            }
        }
        ans = max({ans, dp[u][0], dp[v][0]});
        return up[u][0];
    }
};

class DSU {
public:
    int n;
    vector<int> parent;

    DSU(int n_) {
        n = n_;
        parent.assign(n+1, -1);
    }

    int find(int v) {
        if (parent[v] < 0)
            return v;
        return parent[v] = find(parent[v]);
    }

    void Union(int u,int v) {
        if (parent[u] > parent[v])
            swap(u,v);
        parent[u] += parent[v];
        parent[v] = u;
    }
};

vector<vector<int>> kruskal(int n,vector<edge>& E,int& W) {
    sort(E.begin(), E.end(), [](edge& A,edge& B) {
        return A.w < B.w;
    });
    vector<vector<int>> adj(n+1);
    DSU X(n);
    for (auto e: E) {
        int u = X.find(e.u);
        int v = X.find(e.v);
        if (u != v) {
            X.Union(u,v);
            W += e.w;
            adj[e.u].push_back(e.v);
            adj[e.v].push_back(e.u);
        }
    }
    return adj;
}

void solve() {
    int n,m; cin >> n >> m;
    vector<edge> E(m);
    for (int i = 0; i < m; i++) {
        int u,v,w; cin >> u >> v >> w;
        if (u > v) swap(u,v);
        E[i].u = u;
        E[i].v = v;
        E[i].w = w;
        E[i].id = i;
        mp[{u,v}] = E[i];
    }
    int W = 0;
    vector<vector<int>> MST = kruskal(n, E, W);
    BinaryLifting X(1, MST);    
    vector<int> ans(m);
    for (auto e: E) {
        int u = e.u, v = e.v;
        int mx = 0;
        X.lca(u,v,mx);
        ans[e.id] = W - mx + e.w;
    }
    for (int i: ans) cout << i << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}