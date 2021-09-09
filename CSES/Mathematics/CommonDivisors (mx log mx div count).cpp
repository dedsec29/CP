#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

int const siz = 1e6;
int freq[siz+1];

void solve() {
    int n; cin>>n;
    int mx = 0;
    for (int i=0;i<n;i++) {
        int r; cin>>r;
        freq[r]++;
        mx = max(mx, r);
    } 
    vector<int> gcd_cnt(mx+1);

    for (int i = 1; i <= mx; i++) {
        for (int j = i; j <= mx; j += i)
            gcd_cnt[i] += freq[j];
    }
    for (int i = mx; i >= 1; i--) {
        if (gcd_cnt[i] >= 2) {
            cout << i;
            return;
        }
    }
    cout << 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}