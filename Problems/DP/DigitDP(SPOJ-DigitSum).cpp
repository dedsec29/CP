#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize "trapv"
#define ll long long

ll dp[16][2];
ll poww10[17];

ll solve(string& num,int pos,int tight,vector<ll>& val) {
    if (pos==num.size())
        return 0;
    if (dp[pos][tight]!=-1)
        return dp[pos][tight];
    ll ans = 0;
    ll ub = ((tight==0)?9:(num[pos]-'0'));
    for (ll r=0;r<=ub;r++) {
        if (r==ub && tight==1)  //imp
            ans += r*(val[pos+1]+1)+solve(num,pos+1,1,val);
        else
            ans += r*(poww10[num.size()-pos-1])+solve(num,pos+1,0,val);
    }
    return dp[pos][tight] = ans;
}

void make(vector<ll>& val, string& b) {
    ll z=1;
    for (int i=b.size()-1;i>=0;i--) {
        val[i] = (b[i]-'0')*z + val[i+1];
        z*=10ll;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    poww10[0]=1;
    for (int i=1;i<=16;i++)
        poww10[i] = poww10[i-1]*10ll;
    int t; cin>>t;
    while (t--) {
        ll p,q; cin>>p>>q;
        string a = to_string(max(p-1,0ll));
        string b = to_string(q);
        for (int i=0;i<=b.size();i++)
            dp[i][0]=dp[i][1] = -1;
        vector<ll> val(b.size()+1);
        make(val, b);
        ll R = solve(b,0,1,val); 
        
        vector<ll> v(a.size()+1);
        make(v, a);
        for (int i=0;i<=b.size();i++)
            dp[i][0]=dp[i][1] = -1;
        ll L_1 = solve(a,0,1,v);
        cout<<R-L_1<<"\n";
    }
    return 0;
}