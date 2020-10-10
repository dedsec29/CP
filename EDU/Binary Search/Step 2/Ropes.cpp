#include <bits/stdc++.h>
using namespace std;

int n,k;

bool func(double x, int arr[]) {//can cut at least k pieces of length x 
    int a = 0;
    for (int i=0;i<n;i++) 
        a+= floor(arr[i]/x);
    return (a>=k);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>n>>k;
    int arr[n];
    for (int i=0;i<n;i++) cin>>arr[i];
    double l = 0, r = 1e7+5;
    for (int i=0;i<100;i++) {
        double mid = (l+r)/2;
        if (func(mid,arr)) l=mid;
        else r = mid;
    }
    cout<<fixed<<setprecision(6)<<l;
    return 0;
}