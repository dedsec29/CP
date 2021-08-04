#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

struct interval {
    int l,r,idx;
    ll p;
    bool operator< (const interval& b) const {
        if (l==b.l && r==b.r)
            return idx < b.idx;
        if (r==b.r)
            return l < b.l;
        return r < b.r;
    }
};

//dp[i] = max profit till ith line segment
//maintain best line seg such that doesn't intersect curr line for each i
//dp[i] = current line profit + max(1..best[i])
//sorting by end time cause wanna maintain prefix maximum over increasing right boundary

void solve() {
    int n; cin>>n;
    vector<interval> arr(n);
    for (int i=0;i<n;i++) {
        cin>>arr[i].l>>arr[i].r>>arr[i].p;
        arr[i].idx = i;
    }
    sort(arr.begin(),arr.end());
    vector<int> x(n), y(n);
    for (int i=0;i<n;i++) 
        x[i] = arr[i].l, y[i] = arr[i].r;

    vector<int> best(n, -1);
    for (int i=0;i<n;i++) {
        int pos = lower_bound(y.begin(),y.end(),x[i]) - y.begin();
        pos--;
        if (pos >= 0)
            best[i] = pos;
    }
    vector<ll> dp(n);
    vector<ll> premax(n, 0);
    premax[0] = dp[0] = arr[0].p;
    for (int i=1;i<n;i++) {
        int nice = best[i];
        if (nice == -1) 
            dp[i] = max(arr[i].p, dp[i]); 
        else 
            dp[i] = max(dp[i], arr[i].p + premax[nice]);
        premax[i] = max(premax[i-1], dp[i]);
    }
    cout << *max_element(dp.begin(), dp.end()) ;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}