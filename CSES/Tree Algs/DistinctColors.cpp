#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long	//small to large interval merging

int const siz = 2e5;
vector<int> adj[siz+1];
set<int> vc[siz+1];
int ans[siz+1];

void dfs(int v,int p) {
	int mx = 0, id = 0;
	for (int i: adj[v]) {
		if (i==p) continue;
		dfs(i,v);
		if (mx<vc[i].size()) {
			mx = vc[i].size();
			id = i;
		}
	} 
	if (id==0) {//leaf node
		ans[v] = 1;
		return;
	}
	vc[id].insert(vc[v].begin(),vc[v].end());
	swap(vc[id], vc[v]);	//now v has largest set
	for (int i: adj[v]) {
		if (i==p || i==id) continue;
		vc[v].insert(vc[i].begin(),vc[i].end());
	}
	ans[v] = vc[v].size();
}

void solve() {
    int n; cin>>n;
    for (int i=1;i<=n;i++) {
    	int r; cin>>r;
    	vc[i].insert(r);
    }
    for (int i=1;i<n;i++) {
    	int u,v; cin>>u>>v;
    	adj[u].push_back(v);
    	adj[v].push_back(u);
    }
    dfs(1,0);
    for (int i=1;i<=n;i++) cout<<ans[i]<<" ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}