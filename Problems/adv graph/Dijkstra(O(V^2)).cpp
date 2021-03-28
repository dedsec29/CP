#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const siz = 1e5;
int const inf = 1e9;
vector<pair<int,int>> adj[siz+1];

int main() {
	int n,m; cin>>n>>m;	//number of vertices and edges
    vector<int> d(n+1, inf);
    vector<int> p(n+1, -1);
    vector<bool> marked(n+1, false);
    int source; cin>>source;
    d[source] = 0;

    while (m--) {
    	int u,v,w; cin>>u>>v>>w;
    	adj[u].push_back({v,w});
    	adj[v].push_back({u,w});
    }
    
    int u;
    while (true) {
    	int x = inf;
    	u = -1;
    	for (int i=1;i<=n;i++) {
    		if (!marked[i] && x>=d[i]) {
    			x = d[i];
    			u = i;
    		}
    	}
    	if (u==-1)
    		break;
    	marked[u] = true;
    	for (auto e: adj[u]) {
    		if (d[u] + e.second < d[e.first]) {
    			p[e.first] = u;
    			d[e.first] = d[u] + e.second; 
    		}
    	}
    }

    cout<<"Source = "<<source<<"\n";
    cout<<"v: ";
    for (int i=1;i<=n;i++) 
    	cout<<i<<" ";
    cout<<"\nd: ";
	for (int i=1;i<=n;i++) {
		if (d[i]<inf)
			cout<<d[i]<<" ";
		else
			cout<<"inf ";
	}
	cout<<"\np: ";
	for (int i=1;i<=n;i++) cout<<p[i]<<" ";
    return 0;
}