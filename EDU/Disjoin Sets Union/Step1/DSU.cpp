#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

// Vanilla DSU: Path compression + Union by size
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

void solve() {
    int n,q; cin >> n >> q;
    DSU X(n);
    while (q--) {
        string s; int u,v; cin >> s >> u >> v;
        u = X.find(u);
        v = X.find(v);
        if (s == "union") {
            if (u != v)
                X.Union(u,v);
        }
        else {
            if (u == v) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}