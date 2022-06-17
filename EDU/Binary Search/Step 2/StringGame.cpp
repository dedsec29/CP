#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

// Classic
// subsequence match takes O(t) time
// Brute: t * t, Optimal: tlogt (subsequence matching only logt times)

bool check(int ep,vector<int>& arr,string& t,string& p) {
    int n = t.size();
    int m = p.size();
    vector<bool> taken(n);
    for (int i = 0; i <= ep; i++)
        taken[arr[i]-1] = true;
    int ptr = -1;   // how much matched so far
    for (int i = 0; i < n && ptr != m-1; i++) {
        if (taken[i]) continue;
        if (t[i] == p[ptr+1])
            ptr++;
    }
    return ptr == m-1;
}

void solve() {
    string t,p; cin >> t >> p;
    int n = t.size();
    vector<int> arr(n);
    for (int& i: arr) cin >> i;
    int L = -1, R = n;
    while (R-L > 1) {
        int mid = (L+R)/2;
        if (check(mid, arr, t, p))
            L = mid;
        else
            R = mid;
    }
    cout << L+1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}