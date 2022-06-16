#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

// https://codeforces.com/contest/1131/problem/F
// Why is smaller to large merging O(NlogN)?
// We will always merge smaller set (S1) into larger set (S2)
// (By merge here, we mean adding all members (multiset))
// |S1 + S2| >= 2 |S1|
// Why? Well, |S1 + S2| >= S1 is obvious
// But |S1| < |S2| too
// ... .... => |S1| + |S1| is not enough to cover |S1| + |S2|
// Therefore |S1 + S2| >= 2 |S1|
// This means that every merged set is atleast twice as large the smaller set
// Ofcourse there is a limit to the size this set can expand (N)
// An element therefore can be moved around into merged sets O(log N) times  (cause each time S doubles)
// Each element jumps O(logN) times
// For all, thus, tc is O(NlogN)

class DSU {
public:
    vector<int> parent;
    vector<vector<int>> comp;   // component members

    DSU(int n) {
        parent.resize(n+1);
        comp.resize(n+1);
        for (int i = 1; i <= n; i++)
            parent[i] = i;
        for (int i = 1; i <= n; i++)
            comp[i] = {i};
    }

    int find(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);
    }

    void Union(int u,int v) {
        u = find(u);
        v = find(v);
        if (u == v)
            return;
        // size heuristic, u > v
        if (comp[u].size() < comp[v].size())
            swap(comp[u], comp[v]);
        parent[v] = u;
        while (!comp[v].empty()) {
            comp[u].emplace_back(comp[v].back());
            comp[v].pop_back();
        }
    }
};

void solve() {
    int n; cin >> n;
    DSU dsu(n);
    while (n--) {
        int u,v; cin >> u >> v;
        dsu.Union(u,v);
    }
    // all must be in one component after all operations
    for (int i: dsu.comp[dsu.find(1)]) cout << i << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}