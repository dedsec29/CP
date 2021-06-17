#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const inf = 1e9+1;

void solve() {
    int n; cin>>n;
    vector<int> arr(n);
    for (int i=0;i<n;i++) cin>>arr[i];
    vector<int> d(n+1, inf), prev_lis_index(n+1), index(n+1);
    //d[i] stores the last element of increasing subsequence of length i
    //prev_lis_index[i] stores the index of (i-1)th element in this lis
    //index[i] stores the index of element of lis ending at lenght i
    d[0] = -inf;
    index[0] = prev_lis_index[0] = -1;
    for (int i=0;i<n;i++) {
        int pos = upper_bound(d.begin()+1,d.end(),arr[i])-d.begin();
        index[pos] = i;
        prev_lis_index[index[pos]] = index[pos-1];
        d[pos] = arr[i];
    }
    int ans = 0;
    for (int i=1;i<=n;i++) {
        if (d[i] < inf)
            ans = i;
    }
    cout<<ans<<"\n";
    vector<int> lis;
    int x = index[ans];
    while (x!=-1) {
        lis.push_back(arr[x]);
        x = prev_lis_index[x];
    } 
    reverse(lis.begin(),lis.end());
    for (int i: lis) cout<<i<<" ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}