#include <bits/stdc++.h>
using namespace std;
#define ll long long

int minAssignment(int arr[], int n, int x) {
	int l=-1, r=n;
	while (l<r+1) {
		int mid = l + (r-l)/2;
		if (arr[mid]<x) l=mid;
		else r=mid;
	}
	return r;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m,k; cin>>n>>m>>k;
    ll arr1[n], arr2[m];
    for (int i=0;i<n;i++) cin>>arr1[i];
    for (int i=0;i<m;i++) cin>>arr2[i];
    sort(arr1, arr1+n);
	sort(arr2, arr2+m);
	int ans = 0;
	unordered_map<int, int> mp; // 
	for (int i=0;i<n;i++) {
		int pos = minAssignment(arr2, m, arr1[i]-k);
		if (pos==n) break;
		if ()
	}
    return 0;
}