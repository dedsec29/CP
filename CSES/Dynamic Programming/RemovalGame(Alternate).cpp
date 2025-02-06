#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define int long long

void solve() {
    int n; cin >> n;
    vector<int> A(n);
    for (int& i: A) cin >> i;
    vector<vector<int>> dp(n, vector<int>(n));
    int sum = 0;
    for (int i = 0; i < n; i++) {
        dp[i][i] = A[i];
        sum += A[i];
    }

    for (int block = 2; block <= n; block++) {
        for (int l = 0, r = block-1; r < n; l++, r++) {
            dp[l][r] = max(A[l] - dp[l+1][r], A[r] - dp[l][r-1]);
        }
    }   
    cout << (sum + dp[0][n-1])/2 ;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

/*
    Say that Alice adds to the score, Bob subtracts
    Alice is trying to maximize the score, Bob minimize
    A - B = dp[l][r]
    A + B = sum of all
    A = (sum + dp[0][n-1])/2
*/
