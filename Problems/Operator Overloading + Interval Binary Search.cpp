#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

//https://codeforces.com/contest/976/problem/C
//might have done incorectly, cant bs on y cause not sorted by ending

struct interval {
    int l,r,idx;
    bool operator< (const interval& b) const {
        if (l==b.l && r==b.r)
            return idx < b.idx;
        if (l==b.l)
            return r < b.r;
        return l < b.l;
    }
};

void solve() {
    int n; cin>>n;
    vector<interval> arr(n);
    for (int i=0;i<n;i++) {
        cin>>arr[i].l>>arr[i].r;
        arr[i].idx = i;
    }
    vector<int> x(n), y(n);
    sort(arr.begin(),arr.end());
    for (int i=0;i<n;i++) 
        x[i] = arr[i].l, y[i] = arr[i].r;
    int p=-1,q=-1;
    for (int i=0;i<n;i++) {
        int inc = x.end() - lower_bound(x.begin(),x.end(),arr[i].l);
        int exc = y.end() - upper_bound(y.begin(),y.end(),arr[i].r);
        if (inc-exc >=2) {
            // cout<<inc<<" "<<exc<<", "<<arr[i].l<<" "<<arr[i].r<<endl;
            p = i;
            break;
        }
    }
    if (p==-1) {
        cout<<"-1 -1";
        return;
    }
    for (int i=0;i<n;i++) {
        if (i==p) continue;
        if (arr[i].l >= arr[p].l && arr[i].r <= arr[p].r) {
            q = i;
            break;
        }
    }
    cout<<arr[q].idx+1<<" "<<arr[p].idx+1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}