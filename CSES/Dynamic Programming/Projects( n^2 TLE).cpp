#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long
 
struct seg {
    int l,r,p;  
};
 
bool comp(seg& x,seg& y) {
    return (x.l<y.l) || (x.l==y.l && x.r<y.r);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin>>n;
    vector<seg> events(n);
    for (int i=0;i<n;i++) {
        int a,b,p; cin>>a>>b>>p;
        events[i] = {a,b,p};
    }
    sort(events.begin(), events.end(), comp);
    ll dp[n];
    for (int i=0;i<n;i++) {
        ll ans = events[i].p;
        for (int j=0;j<i;j++) {
            if (events[j].r<events[i].l)
                ans = max(ans, dp[j]+events[i].p);
        }
        dp[i] = ans;
    }
    cout<<(*max_element(dp,dp+n))<<"\n";
    return 0;
}