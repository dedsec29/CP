#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int rightClosest(ll x, ll arr[], int n) {
    int l=-1, r=n;
    while (r>l+1) {
        int mid = (l+r)/2;
        if (arr[mid]<x) l=mid;
        else r= mid;
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,k; cin>>n>>k;
    ll arr[n];
    for (int i=0;i<n;i++) cin>>arr[i];
    sort(arr,arr+n);
    while (k--) {
        ll x; cin>>x;
        cout<<rightClosest(x, arr, n)+1<<"\n"; //1 based idexing
    }
    return 0;
}