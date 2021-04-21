#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const siz = 1e3;
vector<int> adj[siz+1];

struct segment {
	int l,r,v,idx;
};

bool intersects(segment& a,segment& b) {
	if (a.l<=b.l) 
		return (a.r >= b.l);
	return (a.l<=b.r);
}

void solve() {
    int n; cin>>n;
    segment arr[n+1];
    for (int i=1;i<=n;i++) {
    	adj[i].clear();
    	int x,y,z; cin>>x>>y>>z;
    	arr[i] = {x,y,z,i};
    }
    for (int i=1;i<=n;i++) {
    	for (int j=i+1;j<=n;j++) {
    		if (arr[i].v==arr[j].v && intersects(arr[i],arr[j])) {
    			adj[i].push_back(j);
    			adj[j].push_back(i);
    		}
    	}
    }
    vector<int> colour(n+1, -1);
    colour[0] = 0;
    for (int i=1;i<=n;i++) {
    	if (colour[i]!=-1) continue;
    	queue<pair<int,int>> Q;	//node, parent
    	Q.push({i,0});
    	while (!Q.empty()) {
    		int v = Q.front().first;
    		int p = Q.front().second;
    		Q.pop();
    		colour[v] = 1^colour[p];
    		for (int i: adj[v]) {
    			if (colour[i]!=-1) {
    				if (colour[i]!= (1^colour[v])) {
    					cout<<"NO\n";
    					return;
    				}
    			}
    			else {
    				colour[i] = 1^colour[v];
    				Q.push({i,v});
    			}
    		}
    	}
    }
    cout<<"YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin>>t;
    while (t--) 
        solve();
    return 0;
}