#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

// Avoid path compression cause changing parents woul break logic
// Logic: Collect score by climbing up the tree
// Put the points in bank of parent
// But when merging, we don't want money of node I am merging into, so subtract
class DSU {
public:
    struct node {
        int cnt, points;

        node() {}

        node(int v) {
            cnt = 1;
            points = 0;
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
        return find(parent[v]);
    }

    void Union(int u,int v) {
        if (info[u].cnt < info[v].cnt)
            swap(u,v);
        // add v to u's set
        parent[v] = u;
        info[u].cnt += info[v].cnt;
        info[v].points -= info[u].points;
    }

    void add(int v,int x) {  // add x points to parent representative
        v = find(v);
        info[v].points += x;
    }

    int get(int v) {
        if (v == parent[v])
            return info[v].points;
        return info[v].points + get(parent[v]);
    }
};

void solve() {
    int n,q; cin >> n >> q;
    DSU X(n);
    while (q--) {
        string s; cin >> s;
        if (s[0] == 'j') {
            int x,y; cin >> x >> y;
            x = X.find(x);
            y = X.find(y);
            if (x != y)
                X.Union(x, y);
        }
        else if (s[0] == 'a') {
            int v,x; cin >> v >> x;
            X.add(v, x);
        }
        else {
            int v; cin >> v;
            cout << X.get(v) << "\n";
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}