#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; ll x; cin>>n>>x;
    vector<int> weight(n);
    for (int& i: weight) cin>>i;
    int ub = 1<<n;
    vector<pair<ll,ll>> dp(ub);  //f1,f2
    //for subset S, 
    //f1(S) = minimum rides required
    //f2(S) = minimum last ride weight (this greedy works cause exchange arg can be applied)
    //f1(S) = if f2(S-{e}) + weight[e] <=x, = f1(S-{e})     (update f2(S-{e}) += weight[e])
                                    // else = f1(S-{e}) + 1
    //do this for all e in mask (it gives what's the best way to reach this S/mask)
    //we want dp1[00100] such to have value 1, thus dp1[0] = 1
    dp[0] = {1, 0};
    for (int i = 1; i < ub; i++) {
        dp[i] = {n+1, 0};
        //we need to find best value for current mask (which bit best to come from/turn off)
        for (int j = 0; j < n; j++) {
            if (i & (1<<j)) {
                auto option = dp[i ^ (1<<j)];
                if (option.second + weight[j] <= x)
                    option.second += weight[j];
                else {
                    option.first++;
                    option.second = weight[j];
                }
                dp[i] = min(dp[i], option);
            }
        }
    }
    cout << dp[ub-1].first;    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}