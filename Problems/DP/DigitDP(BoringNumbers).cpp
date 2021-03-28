#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize "trapv"
#define ll long long

ll dp[20][2][2]; //pos, first eve=0:odd=1, tight

ll solve(string& num,int pos,int p,int tight) {
    if (pos==num.size()) 
        return 1;
    if (dp[pos][p][tight]!=-1)
        return dp[pos][p][tight];
    ll ans = 0;
    int ub = (tight==0)?9:(num[pos]-'0');
    for (int i=p;i<=ub;i+=2)
        ans += solve(num, pos+1, !p, (tight && i==ub));
    return dp[pos][p][tight] = ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc; cin>>tc;
    for (int t=1;t<=tc;t++) {
        ll p,q; cin>>p>>q;
        string a = to_string(p-1);
        string b = to_string(q);
        memset(dp, -1, sizeof(dp));
        ll R = solve(b,0,1,1);;
        for (int i=1;i<b.size();i++) 
            R += solve(b,i,1,0);
        memset(dp, -1, sizeof(dp));
        ll L = solve(a,0,1,1);;
        for (int i=1;i<a.size();i++) 
            L += solve(a,i,1,0);
        cout<<"Case #"<<t<<": "<<R-L<<"\n";
    }
    return 0;
}