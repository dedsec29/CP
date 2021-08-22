#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; cin>>n;
    vector<pair<int,char>> arr(2*n);
    for (int i=0;i<n;i++) {
        cin>>arr[i].first>>arr[n+i].first;
        arr[i].second = 'i';
        arr[n+i].second = 'o';
    }
    sort(arr.begin(), arr.end());
    int cnt = 0;
    int mx = 0;
    for (auto i: arr) {
        if (i.second == 'i')
            cnt++;
        else
            cnt--;
        mx = max(mx, cnt);
    }
    cout << mx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}