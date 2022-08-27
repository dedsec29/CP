#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

int const siz = 2e5;
vector<int> adj[siz+1];
int euler[2*siz+1], tin[siz+1], tout[siz+1], A[siz+1];

class Fenwick { // 1 based indexing
public:
    int n;
    vector<int> ft;

    Fenwick(int n_) {
        n = n_;
        ft.resize(n+1);
    }

    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += ft[i];
            i -= i&-i;
        }
        return sum;
    }

    void update(int i, int x) {
        while (i <= n) {
            ft[i] += x;
            i += i&-i;
        }
    }

    int query(int l,int r) {
        return query(r) - query(l-1);
    }
};

void dfs(int v,int p,int& timer) {
    ++timer;
    euler[timer] = A[v];
    tin[v] = timer;
    for (int i: adj[v]) {
        if (i == p) continue;
        dfs(i, v, timer);
    }
    ++timer;
    euler[timer] = 0;
    tout[v] = timer;
}

void solve() {
    int n,q; cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i < n; i++) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int timer = 0;
    dfs(1, 0, timer);
    
    Fenwick X(2*n);
    for (int i = 1; i <= 2*n; i++) 
        X.update(i, euler[i]);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int s,x; cin >> s >> x;
            int old = X.query(tin[s], tin[s]);
            X.update(tin[s], x - old);
        }
        else {
            int s; cin >> s;
            cout << X.query(tin[s], tout[s]) << "\n";
        }
    }

}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}