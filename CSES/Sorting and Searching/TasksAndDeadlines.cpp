#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

void solve() {
    int n; cin>>n;
    ll A = 0, B = 0;
    vector<ll> arr(n);
    for (ll& i: arr) {
        cin>>i;
        ll d; cin>>d;
        A += d;
    }
    sort(arr.begin(), arr.end());
    B = arr[0];
    for (int i=1;i<n;i++) arr[i] += arr[i-1];
    for (int i=1;i<n;i++) B += arr[i];
    cout << A-B;
    //reward = Σdi - Σpre[i]
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}