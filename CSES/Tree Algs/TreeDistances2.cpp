#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long
 
int const siz = 2e5;
vector<int> adj[siz+1];
ll sb[siz+1], dp[siz+1], ans[siz+1], res;
int n;
 
void dfs1(int v,int p,int d) {
    sb[v] = 1;
    dp[v] = d;    //pretty much follow this for entire sb dp including p
    for (int i: adj[v]) {
        if (i == p) continue;
        dfs1(i,v,d+1);
        sb[v] += sb[i];
        dp[v] += dp[i]; 
    }
}
 
void dfs2(int v,int p) { 
    ans[v] = res;
    for (int i: adj[v]) {
        if (i == p) continue;
        // save the states
        ll state_v = sb[v], state_i = sb[i], state_res = res, state_dp_i = dp[i], state_dp_v = dp[v];
 
        // do the changes before transition v -> i
        res = (dp[v]-dp[i] + n-sb[i]) + (dp[i] - sb[i]);
        dp[v] = dp[v]-dp[i] + n-sb[i];
        dp[i] = res;
        sb[v] -= sb[i];
        sb[i] = n;
        

        // perform rerouting dp
        dfs2(i,v);
 
        // rollback the states
        sb[v] = state_v;
        sb[i] = state_i;
        res = state_res;
        dp[i] = state_dp_i;
        dp[v] = state_dp_v;
    }
}
 
void solve() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);   
    }
    dfs1(1,0,0);    //calc sb and dp
    res = dp[1];
    dfs2(1,0);
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}