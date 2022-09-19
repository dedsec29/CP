#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

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

struct query {
    char c; int u,v;
};

void solve() {
    int n,m,k; cin >> n >> m >> k;
    DSU X(n);
    while (m--) {
        int u,v; cin >> u >> v;
    }
    vector<query> arr(k);
    for (int i = 0; i < k; i++) {
        string s; int u,v; cin >> s >> u >> v;
        arr[i].c = s[0];
        arr[i].u = u;
        arr[i].v = v;
    }
    vector<int> ans;
    for (int i = k-1; i >= 0; i--) {
        int u = X.find(arr[i].u);
        int v = X.find(arr[i].v);
        if (arr[i].c == 'a') 
            ans.push_back(u == v);
        else {
            if (u != v)
                X.Union(u,v);
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i: ans) {
        if (i) cout << "YES\n";
        else cout << "NO\n";
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}