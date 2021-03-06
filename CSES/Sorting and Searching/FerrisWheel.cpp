#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; ll x; cin>>n>>x;
    ll arr[n];
    for (int i=0;i<n;i++) cin>>arr[i];
    sort(arr, arr+n);
    int l=0, r = n-1, ans =0;
    while (l<r) {
        if (arr[l]+arr[r] <= x) {
            ans++;
            l++;
            r--;
        }
        else {
            ans++;
            r--;
        }
    }
    if (l==r) ans++;
    cout<<ans<<"\n";
    return 0;
}