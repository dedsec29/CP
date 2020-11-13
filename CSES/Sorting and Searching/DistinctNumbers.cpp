#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin>>n;
    unordered_map<int,int> mp;
    mp.reserve(n);
    for (int i=0;i<n;i++) {
    	int r; cin>>r;
    	mp[r]++;
    }
    cout<<mp.size();
    return 0;
}