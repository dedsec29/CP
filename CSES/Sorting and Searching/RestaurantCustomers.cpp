#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

bool comp(pair<int,int>& a,pair<int,int>& b) {
    return (a.second<b.second) || (a.second==b.second && a.first<=b.first);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin>>n;
    pair<int,int> intervals[n];
    for (int i=0;i<n;i++) {
        int a,b; cin>>a>>b;
        intervals[i] = {a, b-1};
    }
    sort(intervals, intervals+n, comp);
    int ans = 0;
    for (int i=0;i<n;i++) {
        
    }
    return 0;
}