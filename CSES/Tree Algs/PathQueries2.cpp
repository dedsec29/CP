#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

int const inf = 1e5;        // used as -inf

template <typename T>
class SparseTable {
public:
    int n, ub;
    vector<vector<T>> sparse;

    SparseTable() {}

    SparseTable(vector<T>& arr) {
        n = arr.size();
        ub = __lg(n);
        sparse = vector<vector<T>>(n, vector<T>(ub + 1));

        for (int i=0;i<n;i++)
            sparse[i][0] = arr[i];
        for (int j=1;j<=ub;j++)
            for (int i=0;i+(1<<j)-1<n;i++)
                sparse[i][j] = min(sparse[i][j-1], sparse[i+(1<<(j-1))][j-1]);
    }

    int query(int l,int r) {
        int interval = r-l+1;
        int jump = __lg(interval);
        return min(sparse[l][jump], sparse[r-(1<<jump)+1][jump]).second;
    }
};

class LCA {
public:
    SparseTable<pair<int,int>> sparse;
    int n;
    vector<int> first, parent;      // parent not necessary for lca
    vector<pair<int,int>> euler;    // depth, vertex

    LCA() {}

    LCA(int root,vector<vector<int>>& adj) { // 1 based indexing of nodes
        n = adj.size()-1;
        first.resize(n+1);
        parent.resize(n+1);
        euler.resize(2*n+1);    // around 2*n because twice the n-1 edges
        int idx = -1;
        dfs(root, 0, 0, idx, adj);
        sparse = SparseTable<pair<int,int>>(euler);
    }

    void dfs(int v,int p,int d,int& idx,vector<vector<int>>& adj) {
        idx++;
        parent[v] = p;
        euler[idx] = {d, v};
        first[v] = idx;
        for (int i: adj[v]) {
            if (i == p) continue;
            dfs(i,v,d+1,idx, adj);
            ++idx;
            euler[idx] = {d, v};
        }
    }

    int lca(int u,int v) {
        if (first[u] > first[v])
            swap(u,v);
        return sparse.query(first[u], first[v]);
    }
};

class SegmentTree {         // RMQ + point updates
public:
    int n;
    vector<int> t;

    SegmentTree() {}

    SegmentTree(int n_) {  // 1 based array
        n = n_;
        t.resize(4*n+1);
        // no need to build here. We build as we HLD
    }

    int query(int v,int tl,int tr,int l,int r) {
        if (l > r)
            return -inf;
        if (l == tl && r == tr)
            return t[v];
        int tm = (tl+tr)>>1;
        return max( query(2*v, tl, tm, l, min(r, tm)), query(2*v+1, tm+1, tr, max(l, tm+1), r) );
    }

    void update(int v,int tl,int tr,int pos,int new_val) {
        if (tl == tr) 
            t[v] = new_val;
        else {
            int tm = (tl + tr)>>1;
            if (pos <= tm) update(2*v, tl, tm, pos, new_val);
            else update(2*v+1, tm+1, tr, pos, new_val);
            t[v] = max(t[2*v], t[2*v+1]);
        }
    }
};

class HLD {
public:
    int n;
    vector<int> A;
    SegmentTree seg;
    LCA X;
    vector<int> sb, depth;
    vector<int> id;     // We label each vertex, so that only one segtree is needed
    // Labelling is done is such a way that all heavy chain nodes 
    // are numbers consecutively. This helps in querying our segtree easily.
    // For a vertex, label all the heavy chain members recursively first, and
    // then only label the other children
    vector<int> chain;     // parent of heavy chain above
    vector<int> heavy_child;    // stores heavy child of ith node

    HLD() {}

    HLD(int n_,vector<int>& arr,vector<vector<int>>& adj) { // 1 based arr and adj
        A = arr;
        n = n_;
        X = LCA(1, adj);
        seg = SegmentTree(n);
        sb.resize(n+1);
        depth.resize(n+1);
        chain.resize(n+1);
        id.resize(n+1);
        heavy_child.resize(n+1);
        dfs_sb(1, adj);
        int timer = 0;
        dfs_hld(1, 1, timer, adj);
    }

    void dfs_sb(int v, vector<vector<int>>& adj) {
        sb[v] = 1;
        depth[v] = depth[X.parent[v]] + 1;
        int child = -1, sz = -1;
        for (int i: adj[v]) {
            if (i == X.parent[v]) continue;
            dfs_sb(i, adj);
            sb[v] += sb[i];
            if (sb[i] > sz) {
                sz = sb[i];
                child = i;
            }
        }
        heavy_child[v] = child;
    }

    void dfs_hld(int v,int top,int& timer,vector<vector<int>>& adj) {
        id[v] = ++timer;
        chain[v] = top;
        seg.update(1, 1, n, id[v], A[v]);

        if (heavy_child[v] == -1) // leaf node
            return;
        dfs_hld(heavy_child[v], top, timer, adj);
        for (int i: adj[v]) {
            if (i == heavy_child[v] || i == X.parent[v]) continue;
            // light edges (top = i)
            dfs_hld(i, i, timer, adj);
        }
    }

    int path_query(int u,int v) {
        int p = X.lca(u,v);
        // construct answer from [u,p) [v, p) and {p}
        return max({path(u, p), path(v, p), A[p]});
    }

    int path(int u,int p) { // Traverse atmost logn light edges => Switch chains logn times atmost
        // Return ans from [u, p) 
        int ans = -inf;
        while (u != p) {    // not gonna happen anyway cause we want [u,p)
            if (chain[u] == u) {    // light edge
                ans = max(A[u], ans);
                u = X.parent[u];
            }
            else if (depth[chain[u]] > depth[p]) { // p and u not in the same chain
                // id of u must be > id of chain parent so query is valid
                ans = max(ans, seg.query(1, 1, n, id[ chain[u] ], id[u] ) );
                u = X.parent[chain[u]];
            }
            else {
                // // when p == u, l > r seg returns -inf
                ans = max(ans, seg.query(1, 1, n, id[p]+1, id[u])); 
                break;
            }
        }
        return ans;
    }

    void update(int v,int new_val) {
        seg.update(1, 1, n, id[v], new_val);
        A[v] = new_val;
    }
};

void solve() {
    int n,q; cin >> n >> q;
    vector<vector<int>> adj(n+1);
    vector<int> A(n+1);
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i < n; i++) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    HLD H(n, A, adj);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int s,x; cin >> s >> x;
            H.update(s, x);
        }
        else {
            int u,v; cin >> u >> v;
            cout << H.path_query(u,v) << " ";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}