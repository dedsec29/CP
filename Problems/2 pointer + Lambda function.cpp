#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

// https://codeforces.com/problemset/problem/1427/B

void solve() {
    int n,k; cin>>n>>k;
    string s; cin>>s;
    vector<pair<int,int>> intervals;
    int sp = 0, ep = n-1;
    while (sp<n && s[sp]=='L') sp++;
    if (sp==n) {
        cout<<max(2*k-1,0)<<"\n";
        return;
    }
    while(ep>=0 && s[ep]=='L') ep--;
    //find all LLL.. (LL |WWWWW LL WWWW LLL WW| LL)
    for (int l=sp,r=sp;r<=ep;r++) {
        if (s[r]=='L') continue;
        if (r-l-1 > 0) 
            intervals.push_back({l+1,r-1});
        l = r;
    }
    sort(intervals.begin(),intervals.end(), [](pair<int,int> const& a,pair<int,int> const& b) {
        return a.second-a.first < b.second-b.first;
    });
    for (auto i: intervals) {
        int p = i.second;
        while (p>=i.first && k>0) {
            s[p] = 'W'; 
            p--, k--;
        }
    }
    sp = 0, ep = n-1;
    while (sp<n && s[sp]=='L') sp++;
    while(ep>=0 && s[ep]=='L') ep--;
    sp--;
    while (sp>=0 && k>0) {
        s[sp] = 'W';
        sp--, k--;
    }
    ep++;
    while (ep<n && k>0) {
        s[ep] = 'W';
        ep++, k--;
    }
    int score = 0;
    for (int i=0;i<n;i++) {
        if (s[i]=='W') {
            if (i==0 || s[i-1]!='W') score++;
            else score += 2;
        }
    }
    cout<<score<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin>>t;
    while (t--) 
        solve();
    return 0;
}