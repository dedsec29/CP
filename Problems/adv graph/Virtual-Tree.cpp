#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

// https://www.codechef.com/START69B/problems/PASSTHRU

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
    vector<int> first, last, parent;      // parent not necessary for lca
    vector<pair<int,int>> euler;    // depth, vertex

    LCA(int root,vector<vector<int>>& adj) { // 1 based indexing of nodes
        n = adj.size()-1;
        first.resize(n+1);
        last.resize(n+1);
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
        last[v] = idx;
    }

    int lca(int u,int v) {
        if (first[u] > first[v])
            swap(u,v);
        return sparse.query(first[u], first[v]);
    }
};

void dfs0(int v,int p,vector<int>& A,vector<vector<int>>& adj) {
    A[v] += A[p];
    for (int i: adj[v]) {
        if (i == p) continue;
        dfs0(i, v, A, adj);
    }    
}

int dist(int u,int v,vector<int>& A,LCA& X) {
    return A[u] + A[v] - A[X.lca(u,v)];
}

void update(int i,int up,int x,vector<int>& diff) {
    // cout << up << " " << i << endl;
    diff[i] += x;
    diff[up] -= x;
}

bool is_ancestor(int a,int b,LCA& X) {
    return X.first[a] <= X.first[b] && X.last[b] <= X.last[a];
}

void dfs1(int v,int p,vector<int>& diff,vector<int>& ans,map<pair<int,int>,int>& edges,vector<vector<int>>& adj) {
    for (int i: adj[v]) {
        if (i == p) continue;
        dfs1(i, v, diff, ans, edges, adj);
        diff[v] += diff[i];
        ans[edges[{min(v,i), max(v,i)}]] = diff[i];
    }
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n+1);
    vector<int> A(n+1), diff(n+1), ans(n+1);
    map<int, vector<int>> col;

    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        col[A[i]].push_back(i);
    }

    map<pair<int,int>, int> edges;
    for (int i = 1; i < n; i++) {
        int u,v; cin >> u >> v;
        if (u > v)
            swap(u, v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges[{u,v}] = i;
    }

    dfs0(1, 0, A, adj); // sum till root
    LCA X(1, adj);

    for (auto it: col) {
        int c = it.first;
        // Build virtual tree
        auto vt_nodes = it.second;
        sort(vt_nodes.begin(), vt_nodes.end(), [&](int a,int b) {
            return X.first[a] < X.first[b];
        });
        int sz = vt_nodes.size();
        for (int i = 0; i < sz-1; i++)
            vt_nodes.push_back(X.lca(vt_nodes[i], vt_nodes[i+1]));
        sort(vt_nodes.begin(), vt_nodes.end(), [&](int a,int b) {
            return X.first[a] < X.first[b];
        });
        vt_nodes.erase(unique(vt_nodes.begin(), vt_nodes.end()), vt_nodes.end());

        stack<int> s;
        s.push(vt_nodes[0]);
        sz = vt_nodes.size();
        for (int i = 1; i < sz; i++) {
            int curr = vt_nodes[i];
            while (!s.empty() && !is_ancestor(s.top(), curr, X)) 
                s.pop();
            // Now s.top() is parent of curr. Edge (s.top(), curr) exists
            update(curr, s.top(), c, diff);
            s.push(curr);
        }
    }

    dfs1(1, 0, diff, ans, edges, adj);
    for (int i = 1; i < n; i++) 
        cout << ans[i] << " ";
    cout << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin>>t;
    while (t--) 
        solve();
    return 0;
}