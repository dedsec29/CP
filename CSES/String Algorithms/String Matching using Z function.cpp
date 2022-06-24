#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

vector<int> z_function(string& s) {
    int n = s.size();
    vector<int> z(n);
    // z0 not well defined
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r)
            z[i] = min(r-i+1, z[i-l]);      // s[l..r] => s[0..r-l] so s[l..i] => s[0..i-l]
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])  // launch
            z[i]++;
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

void solve() {
    string t; cin >> t; // text
    string p; cin >> p; // pattern
    string s = p + "!" + t;      // apply z on this
    vector<int> z = z_function(s);
    int cnt = 0, sp = p.size()+1, n = s.size();
    for (int i = sp; i < n; i++)
        cnt += (z[i] == (int) p.size());
    cout << cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}