#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

// There can be atmost n-1 relaxation phases. Why?
//      Bellman Ford garuantees that in the ith phase,
//      all shortest paths of length i have been found
//      This is obvious, but still a formal way to prove it would be inductively
//      ie if shortest path = (p0, p1, .., pk)
//      Then (p0,p1) found correctly   ans so on
//  The shortesh path consists of atmost n-1 edges, so atmost n-1 phases

// If relaxation still possible after n-1 edges, that means negative cycle exists!
// If no negative cycle, we can stop as soon as a phase did no relaxation

// Bellman Ford is used to find minimum distance, -ve cycle can pose problem
// Negate all edges, then Bellman will find maximum distance, +ve cycle can pose problem

// I have a directed graph (-ve weighted edges possible). I want to reach from Source to 
// Destination with minimum cost. I want to tell if this cost can be -infinity.
// What I tried: 
// If -ve cycle exists, then I will report -inf.
// Problem with this: 
// A negative cycle can exist, but that doesn't mean that path from source to destination
//  involves any negative cycle, ie, 
// a graph can have -ve cycle as well as path cost from source to destination is not -inf.
// My attempt to resolve this:
// Find nodes which are involved in -ve cycle. Now, multisource BFS and mark vertices visited.
// If it marks destination, then report -inf.

struct edge {
    int a,b;
    ll cost;
};

int const siz = 2500;
ll const inf = 1e17;     // n*m*maxW
vector<int> adj[siz+1];

bool BellmanFord(int source,vector<edge>& e,int n,int m,vector<ll>& d) {
    // assume n is the destination
    // return if -ve cycle exists AND it involves destination
    // (cycle may exist but still possible to reach destination)

    d[source] = 0; 
    vector<bool> vis(n+1);
    queue<int> Q;

    for (int phase = 1; phase <= n; phase++) {
        for (auto& i: e) {
            // < inf condition cause then unvisited vertices having d[] = inf, will give
            // inf-1, inf-2, .. edges if edge cost is negative
            if (d[i.a] < inf && d[i.b] > d[i.a] + i.cost) {
                // Good to also check if a + cost doesn't go below -inf (overflow)
                d[i.b] = d[i.a] + i.cost;
                if (phase == n)
                    vis[i.a] = vis[i.b] = true;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (vis[i]) Q.push(i);
    }
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int i: adj[v]) {
            if (!vis[i]) {
                vis[i] = true;
                Q.push(i);
            }
        }
    }
    return vis[n];
}

void solve() {
    int n,m; cin >> n >> m;
    vector<edge> e(m);
    for (int i = 0; i < m; i++) {
        int u,v; ll w; cin >> u >> v >> w;
        adj[u].push_back(v);
        e[i].a = u, e[i].b = v, e[i].cost = -w;
    }
    vector<ll> d(n+1, inf);
    if (BellmanFord(1, e, n, m, d)) cout << -1;
    else cout << -d[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}