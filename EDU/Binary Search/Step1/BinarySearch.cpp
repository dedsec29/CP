#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q; cin>>n>>q;
    int arr[n];
    for (int i=0;i<n;i++) cin>>arr[i];
    while (q--) {
    	int x; cin>>x;
    	int low = 0, high = n-1;
    	bool found = false;
    	while (low<=high) {
    		int mid = (low+high)/2;
    		if (arr[mid]==x) {
    			found=true; break;
    		}
    		else if (arr[mid]<x) low=mid+1;
    		else high = mid-1;
    	}
    	if (found) cout<<"YES\n";
    	else cout<<"NO\n";
    }
    return 0;
}