#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m; cin>>n>>m;
    ll arr[n];
    for (int i=0;i<n;i++) cin>>arr[i];
    int l=0, r=0;
    ll ans = 0, curr=0;
    if (n==1) {
        if (arr[0]<=m) cout<<arr[0];
        else cout<<0;
        return 0;
    }
    
    while (r<n) {
        if (arr[r]+curr<=m) {
            curr += arr[r];
            r++;
        }
        else {
            if (l==r) 
                l++, r++;
            else {
                curr -= arr[l];
                l++;
            }
        }
        ans = max(ans, curr);
        //cout<<l<<" "<<r<<" "<<ans<<endl;
    }
    cout<<ans;
    return 0;
}