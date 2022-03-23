#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long    // no unsigned cause memset to -1 memo

// https://github.com/flash7even/Programming-Contest/blob/master/Code%20Repository/Dynamic%20Programming/Digit%20DP/Digit-DP.cpp
// https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb33e/00000000009e73ea

int const siz = 19; // if 1e18, sz = 19
int const al = 10;
ll dp[siz][2][2][al+1];  // pos, tight, ld?, prev dig

ll work(string& num,int pos,int tight,int ld,int last) {
    if (pos == (int)num.size())
        return 1;
    if (dp[pos][tight][ld][last] != -1)
        return dp[pos][tight][ld][last];
    int ub = (tight == 0) ? 9 : (num[pos]-'0');
    ll ans = 0;
    for (int i = 0; i <= ub; i++) {
        if (i != last || ld == 1) 
            ans += work(num, pos+1, tight && i==ub, ld && i==0, i);
    }
    return dp[pos][tight][ld][last] = ans;
}

void solve() {
    memset(dp, -1, sizeof(dp));
    ll a; string B; cin >> a >> B;
    ll R = work(B, 0, 1, 1, 10);    // 10 => digit that never occurs
    if (a == 0) {
        cout << R << "\n";
        return;
    }
    string A = to_string(a-1ll);
    memset(dp, -1, sizeof(dp));
    ll L = work(A, 0, 1, 1, 10);
    cout << R-L << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}