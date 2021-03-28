#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const siz = 1e5;
int const inf = siz+5;
map<int,int> adj[siz+1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m; cin>>n>>m;
    for (int i=1;i<=m;i++) {
    	int u,v; cin>>u>>v;
        if (u==v)
            continue;
    	adj[u][v] = 0;
    	if (adj[v].find(u)==adj[v].end())
    		adj[v][u] = 1;
    }
    vector<int> dist(n+1, inf);
    dist[1] = 0;
    deque<int> Q;
    Q.push_back(1);
    while (!Q.empty()) {
    	int v = Q.front();
    	Q.pop_front();
    // 	if (v==n)
    // 		break;
    	for (auto i: adj[v]) {
    		if (dist[v] + i.second < dist[i.first]) {
    		    dist[i.first] = dist[v] + i.second;
    		    if (i.second==0)
    			    Q.push_front(i.first);
    		    else
    			    Q.push_back(i.first);   
    		}
    	}
    }
    if (dist[n]!=inf)
        cout<<dist[n];
    else cout<<"-1";
    return 0;
}