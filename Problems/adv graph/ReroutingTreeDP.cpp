#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long
#define ld long double

int const siz = 5e5;
ll const mod = 1e9+7;
vector<int> adj[siz+1];
ld curr, res;
int dt,cv,n;

void dfs(int v,int p,vector<int>& sb) {
    for (int i: adj[v]) {
        if (i==p)
            continue;
        dfs(i,v,sb);
        sb[v] += sb[i];
    }
    sb[v]++;
}

void dfs2(int v,int p,vector<int>& sb) {
    if (curr==res) {
        if (v>cv)
            cv = v;
    }
    else if (curr>res) {
        curr = res;
        cv = v;
    }
    
    for (int i: adj[v]) {
        if (i==p) 
            continue;
        //before traversing (v,i), make the transition changes
        int sbv = sb[v], sbi = sb[i];
        ld resp = res;
        
        res -= (ld) log2(1.0*sb[i]);
        sb[v] -= sb[i];
        sb[i] = n;
        res += (ld) log2(1.0*sb[v]);
        
        dfs2(i,v,sb);
        
        //roll back the changes
        sb[i] = sbi;
        sb[v] = sbv;
        res = resp;
    }
}

void dfs3(int v,int p,vector<int>& sb) {
    if (v!=dt) {
        if (curr==res) {
            if (v>cv)
                cv = v;
        }
        else if (curr>res) {
            curr = res;
            cv = v;
        }
    }
    
    for (int i: adj[v]) {
        if (i==p) 
            continue;
        //before traversing (v,i), make the transition changes
        int sbv = sb[v], sbi = sb[i];
        ld resp = res;
        
        res -= (ld) log2(1.0*sb[i]);
        sb[v] -= sb[i];
        sb[i] = n;
        res += (ld) log2(1.0*sb[v]);
        
        dfs3(i,v,sb);
        
        //roll back the changes
        sb[i] = sbi;
        sb[v] = sbv;
        res = resp;
    }
}

ll fact(int n) {
    ll f = 1;
    for (ll i=1;i<=n;i++) 
        f = (f*i)%mod;
    return f;
}

ll poww(ll A,ll N) {
    ll temp;
    if (N==0)
        return 1;
    temp=poww(A,N/2);
    if (N&1ll)
        return (A*((temp*temp)%mod))%mod;
    else
        return (temp*temp)%mod;
}

void answer(int v,vector<int>& sb,ll fn) {
    dfs(v,0,sb);
    ll ff = 1;
    for (int i=1;i<=n;i++)
        ff = (ff* ((ll)sb[i]))%mod;
    ll q = poww(ff, mod-2);
    q = (fn*q)%mod;
    cout<<v<<" "<<q<<"\n";
}

void solve() {
    int k; cin>>n>>k;
    if (n==1) {
        cout<<"1\n";
        return;
    }
    for (int i=1;i<=n;i++)
        adj[i].clear();
    ll fn = fact(n);
    vector<int> sb(n+1);
    for (int i=1;i<n;i++) {
        int u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    curr = 0;
    dfs(1,0,sb);
    ld f = 0;
    for (int i=1;i<=n;i++)
        f += (ld) log2(1.0*sb[i]);
    curr = res = f;  //minimize
    cv=1;
    
    dfs2(1,0,sb);

    for (int i=1;i<=n;i++)
        sb[i] = 0;
    if (k==1) {
        answer(cv, sb, fn);
        return;
    }
    //for k = 2
    dt = cv;
    for (int i=1;i<=n;i++)
        sb[i] = 0;
    if (cv==2) cv=1;
    else cv=2;
    
    dfs(cv,0,sb);
    f = 0;
    for (int i=1;i<=n;i++)
        f += (ld) log2(1.0*sb[i]);
    curr = res = f;  //minimize
    dfs3(cv,0,sb);
    for (int i=1;i<=n;i++)
        sb[i] = 0;
    answer(cv, sb, fn);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin>>t;
    while (t--) 
    	solve();
    return 0;
}