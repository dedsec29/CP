#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; cin>>n;
    ll x; cin>>x;
    vector<pair<ll,int>> arr(n);
    for (int i=0;i<n;i++) {
        cin>>arr[i].first;
        arr[i].second = i;
    }
    sort(arr.begin(), arr.end());
    int l=0, r=n-1;
    int a = -1, b = -1;
    while (l < r) {
        if (arr[l].first + arr[r].first == x) {
            a = arr[l].second, b = arr[r].second;
            break;
        }
        if (arr[l].first + arr[r].first < x)    //increase the search space
            l++;
        else        //decrease the search space
            r--;
    }   
    if (a == -1) cout << "IMPOSSIBLE";
    else cout << a+1 << " " << b+1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}