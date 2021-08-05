#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

//https://coderevilbuggy.blogspot.com/2018/05/broken-profile-dynamic-programming.html
//explains it all (read each line meticulously, has all answers)

ll const mod = 1e9+7;

bool occupied(int cell,int mask) {
    //cell is 1 indexed
    return (1<<(cell-1)) & mask;
}

void search(int row,int column,int p,int q, vector<vector<ll>>& dp,int n,int m) {
    if (row == n+1) {   //finally done with filling q
        dp[column+1][p] = (dp[column+1][p] + dp[column][q])%mod;
        return;
    }
    if (occupied(row, q)) {
        search(row+1,column,p,q, dp,n,m);
        return;
    }
    //curr cell not occupied, is the below one occupied? (vertical placement)
    if (row+1 <= n && !occupied(row+1, q)) {
        search(row+2, column, p,q, dp,n,m); //we fill it, so i+1 th col will have these off in p
    }
    if (column+1 <= m) {//can I place horizontally
        search(row+1, column, p ^ (1<<(row-1)), q, dp,n,m);
    }
}

void solve() {
    int n,m; cin>>n>>m;
    vector<vector<ll>> dp(m+1, vector<ll>(1<<n));
    dp[0][0] = 1;
    //dp[i][mask] = number of ways to fill such that first i columns arre filled,
    //and (i+1)th column has profile = mask
    // we will dp[i+1][p] += dp[i][q] 
    //p: profile after placing, q: current i's profile
    for (int i = 0; i < m; i++) {
        for (int q = 0; q < (1<<n); q++) {  
            search(1,i,0,q, dp,n,m);
        }
    }
    cout<< dp[m][0] ;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}