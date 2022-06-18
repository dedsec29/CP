#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

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

void dfs(int v,int p,vector<int>& score,vector<vector<int>>& adj) {
    for (int i: adj[v]) {
        if (i == p) continue;
        dfs(i,v, score,adj);
        score[v] += score[i];
    }
}

void solve() {
    int n,m; cin >> n >> m;
    vector<vector<int>> adj(n+1);
    vector<int> score(n+1);

    for (int i = 1; i < n; i++) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    LCA X(1, adj);
    while (m--) {
        int u,v; cin >> u >> v;
        int p = X.lca(u,v);
        if (u == v) {
            score[u]++;
            score[X.parent[u]]--;
        }
        else if (p == u) {
            score[v]++;
            score[X.parent[u]]--;
        }
        else if (p == v) {
            score[u]++;
            score[X.parent[v]]--;
        }
        else {
            score[u]++;
            score[v]++;
            score[p]--;
            score[X.parent[p]]--;
        }
    }
    
    dfs(1, 0, score, adj);
    for (int i = 1; i <= n; i++) cout << score[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}