#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const siz = 2e5;
vector<int> adj[siz+1];
int parent[siz+1];
int diameter,ex;
 
void dfs(int v,int d,int p) {
    parent[v] = p;
    if (diameter <= d) {    // must be <= 
        diameter = d;
        ex = v;
    }
    for (int i: adj[v]) {
        if (i == p) continue;
        dfs(i,d+1,v);
    }
}

void solve() {
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0,-1);
    int source = ex;
    parent[source] = -1;
    dfs(source,0,-1);
    int x = ex;
    vector<int> ans(n+1, -1);
    queue<int> Q;
    int c = 0;
    while (x != -1) {
        ans[x] = max(c, diameter-c);
        Q.push(x);
        x = parent[x];
        c++;
    }
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int i: adj[v]) {
            if (ans[i] == -1) {
                ans[i] = ans[v]+1;
                Q.push(i);
            }
        }
    }
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}