#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const siz = 1e5;
vector<int> adj[siz+1];
int indegree[siz+1];

vector<int> topological_sort(int n) {
    queue<int> Q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0)
            Q.push(i);
    }
    vector<int> order;
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        order.push_back(v);
        for (int i: adj[v]) {
            if (indegree[i] == 0)
                continue;
            indegree[i]--;
            if (indegree[i] == 0)
                Q.push(i);
        }
    }
    if ((int)order.size() != n) 
        order.clear();
    return order;
}

void solve() {
    int n,m; cin >> n >> m;
    bool selfloop = false;
    while (m--) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
        if (u == v) selfloop = true;
    }
    if (selfloop) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    vector<int> topo = topological_sort(n);
    if (topo.empty()) cout << "IMPOSSIBLE\n";
    else {
        for (int i: topo) cout << i << " ";
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}