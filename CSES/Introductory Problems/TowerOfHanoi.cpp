#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize "trapv"
#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2,sse,sse2,sse3,sse4,popcnt,fma") 
#pragma GCC optimize("unroll-loops")
#define ll long long

// n discs from A to C using B = n-1 on B and last on A then n-1 on C
vector<pair<int,int>> ans;

//          source, medium, destination
void f(int n,int a,int b,int c) {
    if (n < 1) return;
    f(n-1, a, c, b);
    ans.push_back({a, c});
    f(n-1, b, a, c);
}

void solve() {
    int n; cin >> n;
    f(n, 1, 2, 3);
    cout << ans.size() << "\n";
    for (auto i: ans) cout << i.first << " " << i.second << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}