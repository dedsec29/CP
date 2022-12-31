#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

int const mod = 1e9+7;
int const siz = 1e5;
vector<int> adj[siz+1];
int indegree[siz+1];
bool descendant[siz+1]; // descendant of 1?

void solve() {
    int n,m; cin >> n >> m;
    while (m--) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
    }

    vector<int> dp(n+1);
    dp[1] = 1;
    queue<int> Q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0)
            Q.push(i);
    }
    descendant[1] = 1;    

    // add to queue only when all dependecies processed
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int i: adj[v]) {
            indegree[i]--;
            if (descendant[v]) {
                descendant[i] = true;
                dp[i] = (dp[i] + dp[v]) % mod;
            }
            if (indegree[i] == 0)
                Q.push(i);
        }
    }
    cout << dp[n];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}