// https://atcoder.jp/contests/abc247/tasks/abc247_e
// In 2 pounter, remember, while adding contribution count,
// FIX a boundary compulsorily

// Also this problem teaches you about Inclusion - Inclusion
// Overall educational problem

#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#define ll long long

ll func(vector<int>& arr,int X,int Y) {
    int n = arr.size();
    // how many subarrays having both X and Y present
    ll ans = 0;
    int l = 0, r = 0;
    int fx = 0, fy = 0;
    while (l < n) {
        while (r < n && (fx == 0 || fy == 0)) {
            if (arr[r] == X) fx++;
            if (arr[r] == Y) fy++;
            r++;
        }
        if (fx != 0 && fy != 0) 
            ans += (ll) (n - (r-1));
        if (arr[l] == X) fx--;
        if (arr[l] == Y) fy--;
        l++;
    }
    return ans;
}

void solve() {
    int n; cin >> n;
    int X,Y; cin >> X >> Y;
    vector<int> arr(n);
    for (int& i: arr) cin >> i;
    ll ans = 0;
    // extract segments haing mn <= Y and X <= mx
    // Then we just need to find how many segments continan both X and Y
    for (int i = 0; i < n; i++) {
        if (arr[i] > X || arr[i] < Y)
            continue;
        vector<int> v;
        int j = i;
        int mx = arr[i];
        int mn = arr[i];
        while (j < n && arr[j] <= X && arr[j] >= Y)
            v.push_back(arr[j++]);
        j--;
        ans += func(v,X,Y);
        i = j;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}