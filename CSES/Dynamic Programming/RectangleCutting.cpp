#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define inf 100000

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a,b; cin>>a>>b;
    if (a>b) swap(a,b);
    vector<vector<int>> dp(a+1, vector<int>(b+1));
    dp[0][0]=inf;
    for (int i=1;i<=b;i++) dp[0][i]=inf, dp[1][i]=i-1;
    for (int i=1;i<=a;i++) dp[i][0]=inf, dp[i][1]=i-1;
    for (int i=1;i<=a;i++) dp[i][i]=0;
    for (int i=2;i<=b;i++) {
        for (int j=2;j<=a;j++) {
            if (i==j) continue;
            int d=inf;
            for (int k=1;k<i;k++)
                d=min(d, dp[j][i-k]+dp[j][k]);
            d++;
            int e=inf;
            for (int k=1;k<j;k++)
                e=min(e, dp[j-k][i]+dp[k][i]);
            e++;
            dp[j][i]=min(d,e);
        }
    }
    cout<<dp[a][b];
    return 0;
}