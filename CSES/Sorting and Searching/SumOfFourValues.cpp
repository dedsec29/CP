#include <bits/stdc++.h>
using namespace std;
#define int long long
 
struct int_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
 
void solve() {
    int n,x; cin >> n >> x;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
 
    unordered_map<int, pair<int,int>, int_hash> mp;
    vector<int> indices;
 
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (mp.count(x - arr[i] - arr[j])) {
                indices = {i,j, mp[x-arr[i]-arr[j]].first, mp[x-arr[i]-arr[j]].second};
                goto here;
            }
        }
        for (int j = 0; j < i; j++)
            mp[arr[i] + arr[j]] = {i,j};   
    }
 
    here:
    if (indices.empty())
        cout << "IMPOSSIBLE\n";
    else {
        for (int i: indices)
            cout << i+1 << " ";
        cout << "\n";
    }
}
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}