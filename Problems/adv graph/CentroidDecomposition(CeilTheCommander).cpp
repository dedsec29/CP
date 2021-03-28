#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const siz = 1e5;
set<int> adj[siz+1];	//change to undordered for O(const)
int sb[siz+1], ans[siz+1];
bool imp;

int dfs(int v,int p) {
	sb[v] = 1;	//this impl doesn't require to clear sb after every decompostion
	for (int i: adj[v]) {
		if (i==p) continue;
		sb[v] += dfs(i,v);
	}
	return sb[v];
}

int find_centroid(int v,int p,int sz) {
	for (int i: adj[v]) {
		if (i!=p && sb[i]>sz/2) 
			return find_centroid(i,v,sz);
	}
	return v;
}

void decompose(int v,int p) {	//p is centroid of prev decomp, v is any node from p's component
	int sz = dfs(v, 0);
	int centroid = find_centroid(v,p,sz);
	ans[centroid] = ans[p]+1;
	if (ans[centroid]>26)
		imp = true;
	for (int i: adj[centroid]) {
		adj[i].erase(centroid);	//delete edges
		decompose(i, centroid);	//decompose each component formed afer deleting
	}
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin>>n;
    for (int i=1;i<n;i++) {
    	int u,v; cin>>u>>v;
    	adj[u].insert(v);
    	adj[v].insert(u);
    }
    decompose(1, 0);
    if (imp) cout<<"Impossible!";
    else for (int i=1;i<=n;i++) cout<<(char)('A'+ans[i]-1)<<" ";
    return 0;
}