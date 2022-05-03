#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

// https://codeforces.com/blog/entry/45223
// https://codeforces.com/contest/165/problem/E

// let y be toggle of x
// compatible to x a number would be such that 
// it has all the zeroes same as y, 1s can be anything
// therefore all submasks of y are compatible to x
// sos dp => 22 * 2^22

void solve() {
    int n; cin >> n;
    vector<int> arr(n);
    for (int& i: arr) cin >> i;
    int ub = 1<<22;
    vector<pair<bool, int>> dp(ub);
    for (int i = 0; i < n; i++) 
        dp[arr[i]] = {true, i};
    for (int i = 0; i < 22; i++) {
        for (int mask = 0; mask < ub; mask++) {
            if ((mask & (1<<i)) && dp[mask ^ (1<<i)].first) 
                dp[mask] = dp[mask ^ (1<<i)];
        }
    }
    for (int i: arr) {
        int inv = i ^ (ub-1);
        auto v = dp[inv];
        if (v.first) cout << arr[dp[inv].second] << " ";
        else cout << "-1 "; 
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}