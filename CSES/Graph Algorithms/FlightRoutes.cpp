#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

// https://codeforces.com/blog/entry/102085

int const siz = 1e5;
vector<pair<int,int>> adj[siz+1];

void solve() {
    int n,m,k; cin >> n >> m >> k;
    while (m--) {
        int u,v,w; cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
    }

    vector<int> cnt(n+1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, 1});
    while (cnt[n] < k) {
        int d = pq.top().first;
        int v = pq.top().second;
        pq.pop();
        if (cnt[v] == k)
            continue;
        cnt[v]++;
        if (v == n)
            cout << d << " ";
        for (auto i: adj[v])
            pq.push({d + i.second, i.first});
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}