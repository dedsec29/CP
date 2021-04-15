#include <bits/stdc++.h>
using namespace std;
#define A 1000001
#define ll long long
ll const m=1e9+7;
int const siz=1e6+5;
int n, level[siz], parent[siz];
vector<int> adj[siz];
unordered_map<int,int> factors[siz];
bool vis[siz];

bitset <A> bits;
int primes[A];

void precomputation(){
    for(int i = 2; i < A; i += 2)	primes[i] = 2 ;
	int sq=sqrt(A-1);
    for(int i = 3; i < A; i += 2) {
        if (!bits[i]){
            primes[i] = i;
            if(i<=sq) for(int j = i * i; j < A; j += 2 * i) {
                if (!bits[j]){
                    primes[j] = i ;
                    bits[j] = 1 ;
                }
            }
        }
    }
}

void perform(int f, int N) {
    unordered_map<int,int> mp;
    int z=N;
    int curr = primes[z];
    int cnt = 1;
    while (z > 1) {
        z /= primes[z];
        if (curr == primes[z]) {
            cnt++; 
            continue; 
        } 
        mp.insert({curr,cnt});
        curr = primes[z]; 
        cnt = 1; 
    }
    factors[f]=mp;
}

void clear() {
    for (int i=1;i<=n;i++)
        adj[i].clear(), vis[i]=false, factors[i].clear();
}

void dfs(int v, int p, int lvl) {
    vis[v]=true;
    level[v]=lvl;
    parent[v]=p;
    for (auto i: adj[v]) {
        if (!vis[i])
            dfs(i,v,lvl+1);
    }
}

unordered_map<int,int> finalc; //don't forget to clear this

ll final() {
    ll res=1;
    for (auto i: finalc) {
        ll p=i.second+1;
        res=((res%m)*(p%m))%m; 
    }
    finalc.clear();
    return res;
}

void addtofinal(int b) {
    unordered_map<int,int> w(factors[b]);
    for (auto x:w) {
        auto it=finalc.find(x.first);
        if (it==finalc.end())
            finalc[x.first]=x.second;
        else
            finalc[it->first]=it->second + x.second;
    }
}

ll lca(int a, int b) {
    int d=level[b]-level[a];
    while (d>0) {
        addtofinal(b);
        b=parent[b];
        d--;
    }
    
    if (a==b) {
        addtofinal(b);
        return final();
    }
    
    while (a!=b) {
        addtofinal(a); a=parent[a];
        addtofinal(b); b=parent[b];
    }
    addtofinal(b);
    return final();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precomputation();
    primes[1]=-1;
    int t; cin>>t;
    while (t--) {
        cin>>n;
        for (int in=1;in<n;in++) {
            int u,v; cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int f=1;f<=n;f++) {
            int x; cin>>x;
            perform(f,x);
        }
        
        //prepare levels and parents
        dfs(1,-1,0);
        int q; cin>>q;
        while (q--) {
            int u,v; cin>>u>>v;
            if (level[u]>level[v]) swap(u,v);
            cout<<lca(u,v)<<"\n";
        }
        clear();
    }
    return 0;
}