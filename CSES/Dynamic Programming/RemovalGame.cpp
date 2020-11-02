#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const siz = 5e3;
ll dp[2][siz+1][siz+1];
ll A[siz+1];

ll solve(bool player1,int l,int r) {
    if (l>r)
        return 0;
    if (player1) {
        if (dp[1][l][r]!=-1)
            return dp[1][l][r];
        return dp[1][l][r] = max(solve(false,l,r-1)+A[r], solve(false,l+1,r)+A[l]);
    }
    if (dp[0][l][r]!=-1)
        return dp[0][l][r];
    return dp[0][l][r] = min(solve(true,l,r-1), solve(true,l+1,r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin>>n;
    for (int i=0;i<2;i++) for (int j=0;j<=n;j++) for (int k=0;k<=n;k++) dp[i][j][k]=-1;
    for (int i=1;i<=n;i++) cin>>A[i];
    cout<<solve(true,1,n);
    return 0;
}