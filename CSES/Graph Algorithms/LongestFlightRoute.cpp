#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const siz = 1e5;
vector<int> adj[siz+1];
int indegree[siz+1], dist[siz+1], parent[siz+1];
bitset<siz+1> descendant;   //descendant of 1

vector<int> work(int n) {
    queue<int> Q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            Q.push(i);
            dist[i] = 1;
        }
        parent[i] = -1;
    }
    descendant[1] = 1;
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int i: adj[v]) {
            if (indegree[i] == 0)
                continue;
            if (descendant[v])
                descendant[i] = 1;
            if (descendant[v] && dist[i] < dist[v] + 1) {   //gotta do dis cause many irrelevant indegs
                dist[i] = dist[v] + 1;
                parent[i] = v;
            }
            indegree[i]--;
            if (indegree[i] == 0) 
                Q.push(i);
        }
    }
    vector<int> v;
    if (!descendant[n])
        return v;
    int x = n;
    while (x != -1) {
        v.push_back(x);
        x = parent[x];
    }
    reverse(v.begin(), v.end());
    return v;
}

void solve() {
    int n,m; cin >> n >> m;
    while (m--) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        indegree[v]++;
    }    
    vector<int> v = work(n);
    if (v.empty()) cout << "IMPOSSIBLE\n";
    else {
        cout << v.size() << "\n";
        for (int i: v) cout << i << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}