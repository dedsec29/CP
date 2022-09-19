#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

class DSU {
public:
    struct node {
        int cnt, mx, mn;

        node() {}

        node(int v) {
            cnt = 1;
            mx = mn = v;
        }
    };

    int n;
    vector<int> parent;
    vector<node> info;

    DSU(int n_) {
        n = n_;
        parent.resize(n+1);
        info.resize(n+1);
        for (int i = 1; i <= n; i++) {
            info[i] = node(i);
            parent[i] = i;
        }
    }

    int find(int v) {
        if (parent[v] == v)
            return v;
        return parent[v] = find(parent[v]);
    }

    void Union(int u,int v) {
        if (info[u].cnt < info[v].cnt)
            swap(u,v);
        // add v to u's set
        parent[v] = u;
        info[u].cnt += info[v].cnt;
        info[u].mx = max(info[u].mx, info[v].mx);
        info[u].mn = min(info[u].mn, info[v].mn);
    }
};

void solve() {
    int n,q; cin >> n >> q;
    DSU X(n);
    while (q--) {
        string s; cin >> s;
        if (s == "union") {
            int u,v; cin >> u >> v;
            u = X.find(u);
            v = X.find(v);
            if (u != v)
                X.Union(u,v);
        }
        else {
            int v; cin >> v;
            v = X.find(v);
            cout << X.info[v].mn << " " << X.info[v].mx << " " << X.info[v].cnt << "\n";
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}