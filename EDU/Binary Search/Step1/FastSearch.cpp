#include <bits/stdc++.h>
using namespace std;

int closestLeft(int x, int arr[],int n) {
    int l=-1, r=n;
    while (r>l+1) {
        int mid = (l+r)>>1;
        if (arr[mid]<=x) l=mid;
        else r=mid;
    }
    return l;
}

int closestRight(int x,int arr[],int n) {
    int l=-1, r=n;
    while (r>l+1) {
        int mid = (l+r)>>1;
        if (arr[mid]<x) l=mid;
        else r=mid;
    }
    return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin>>n;
    int arr[n];
    for (int i=0;i<n;i++) cin>>arr[i];
    sort(arr,arr+n);
    int k; cin>>k;
    while (k--) {
        int l,r; cin>>l>>r;
        cout<<closestLeft(r,arr,n)-closestRight(l,arr,n)+1<<" ";
    }
    return 0;
}