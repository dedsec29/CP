#include <bits/stdc++.h>
using namespace std;
//https://www.youtube.com/watch?v=MiqoA-yF-0M
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string A,B; cin>>A>>B; //A-> B|
    int sA=A.size(), sB=B.size();
    int dp[sB+1][sA+1];
    dp[0][0]=0;
    for (int i=1;i<=sA;i++) dp[0][i]=i;
    for (int i=1;i<=sB;i++) dp[i][0]=i;
    for (int i=1;i<=sB;i++) {
        for (int j=1;j<=sA;j++) {
            if (B[i-1]==A[j-1])
                dp[i][j]=dp[i-1][j-1];
            else
                dp[i][j]=1+min({dp[i-1][j-1], dp[i][j-1], dp[i-1][j]}); //replace|delete|insert
        }
    }
    cout<<dp[sB][sA];
    return 0;
}